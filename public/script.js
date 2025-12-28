function updateMemoryUsage() {
    let usedBytes = 0;

    // Check if the non-standard Chrome API exists
    if (window.performance && window.performance.memory) {
        usedBytes = window.performance.memory.usedJSHeapSize;
    } else {
        // Fallback for Firefox/Safari (Simulate it or show N/A)
        usedBytes = 50 * 1024 * 1024; // Fake 50MB
    }

    // CALL THE C FUNCTION
    // Implementation depends on how you compiled (Emscripten example below):
    // _set_system_memory is the C function name (often prefixed with _)
    Module._set_system_memory(usedBytes);
}

setInterval(updateMemoryUsage, 1000);

async function boot() {
    const response = await fetch('kernel.wasm');
    const buffer = await response.arrayBuffer();
    const { instance } = await WebAssembly.instantiate(buffer);

    const { greetings, memory } = instance.exports;
    const pointer = greetings();
    console.log(`Pointer received from C: ${pointer}`);


    const memoryView = new Uint8Array(memory.buffer);
    
    // Scan from the pointer until we find 0 (null terminator)
    let currentByte = pointer;
    while (memoryView[currentByte] !== 0) {
        currentByte++; // Move to next byte
    }
    
    // Slice the byte array from Start to End
    const stringBytes = memoryView.slice(pointer, currentByte);

    // Decode Bytes -> Text
    const text = new TextDecoder('utf-8').decode(stringBytes);


    document.getElementById('terminal-output').innerText = `[Success]: ${text}`;
}

boot();