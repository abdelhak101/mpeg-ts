class TSHeader {
    constructor() {
        this.sync_byte = 0;
        this.transport_error_indicator = 0;
        this.payload_unit_start_indicator = 0;
        this.transport_priority = 0;
        this.PID = 0;
        this.transport_scrambling_control = 0;
        this.adaptation_field_control = 0;
        this.continuity_counter = 0;
    }
}

function parseHeader(buffer) {
    let header = new TSHeader();
    header.sync_byte = buffer[0];
    header.transport_error_indicator = (buffer[1] & 0x80) >> 7;
    header.payload_unit_start_indicator = (buffer[1] & 0x40) >> 6;
    header.transport_priority = (buffer[1] & 0x20) >> 5;
    header.PID = ((buffer[1] & 0x1F) << 8) | buffer[2];
    header.transport_scrambling_control = (buffer[3] & 0xC0) >> 6;
    header.adaptation_field_control = (buffer[3] & 0x30) >> 4;
    header.continuity_counter = buffer[3] & 0x0F;
    return header;
}

// Assume that 'data' is a Buffer or Uint8Array containing your MPEG-TS data
let data = new Uint8Array(/* Your MPEG-TS data here */);
for (let i = 0; i < data.length; i += 188) {
    let packet = data.slice(i, i + 188);
    let header = parseHeader(packet);
    // Now you can access the fields of the header
    console.log("PID: " + header.PID);
}
