
let memory;             // For accessing WASM memory buffer
let get_g_input_buffer; // The specific C function to get the input pointer
const Module = {};      // The object for mapping C exports
let batteryManager = null;





/**
 * @brief Writes string into a buffer in shared memory with the webAssembly
 * @param {*} str The string that is being written
 * @returns Returns the pointer of the string in shared memory
 */
function writeStringToMemory(str) {
    const ptr = get_g_input_buffer(); // The shared address buffer
    const encoder = new TextEncoder();
    const bytes = encoder.encode(str + "\0");
    const memoryView = new Uint8Array(memory.buffer);
    memoryView.set(bytes, ptr);
    return ptr;
}


/**
 * @brief The async function called in boot to return. This way the promise from navigator.getBattery is called only once.
 */
async function initBattery() {
    if (navigator.getBattery) {
        batteryManager = await navigator.getBattery();
        
        batteryManager.addEventListener('levelchange', updateBatteryStats);
    }
}

/**
 * @brief The synchronous update function. Will run if the promise is resolved, will not if not
 */
function updateBatteryStats() {
    if (batteryManager) {
        const level = Math.floor(batteryManager.level * 100);
        Module._set_system_battery(level);
    }
}


/**
 * @brief Updates stats frequently (every 100ms)
 * Updates: Memory usage 
 */
function updateFrequentStats(){
    if(window.performance && window.performance.memory){
        Module._set_memory_usage(performance.memory.usedJSHeapSize);
    }
    // The default case is already in the backend
    
}

/**
 * @brief Updates stats infrequently (every 1000ms)
 * Updates: Battery
 */
function updateInfrequentStats(){
    updateBatteryStats();
}

/**
 * @brief Fetches the static system status once
 * Updates: Resolution, terminal, cpu count, RAM, Locale
 */
function updateOnceStats(){
    Module._set_window_width(window.screen.width);
    Module._set_window_height(window.screen.height);

    let ptr = writeStringToMemory(navigator.userAgent);
    Module._set_terminal(ptr);

    if(navigator.hardwareConcurrency) 
        Module._set_system_cores(navigator.hardwareConcurrency);
    
    if(navigator.deviceMemory) 
        Module._set_system_ram(navigator.deviceMemory);

    writeStringToMemory(navigator.language);
    Module._set_locale(ptr);
}


async function boot() {
    const response = await fetch('kernel.wasm');
    const buffer = await response.arrayBuffer();

    const { instance } = await WebAssembly.instantiate(buffer);
    const exports = instance.exports;

    memory = exports.memory;
    get_g_input_buffer = exports.get_g_input_buffer; 

    Module._set_window_width = exports.set_window_width;
    Module._set_window_height = exports.set_window_height;
    Module._set_terminal = exports.set_terminal;
    Module._set_system_cores = exports.set_system_cores;
    Module._set_system_ram = exports.set_system_ram;
    Module._set_locale = exports.set_locale;
    Module._set_memory_usage = exports.set_memory_usage;
    Module._set_system_battery = exports.set_system_battery;
    
    updateOnceStats(); 
    initBattery();
    setInterval(updateFrequentStats, 1000);
    setInterval(updateInfrequentStats, 7000);
}

boot();


