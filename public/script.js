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