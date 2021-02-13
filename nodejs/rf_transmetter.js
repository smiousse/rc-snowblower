const nrf24=require("nrf24"); // Load de module

 // Init the radio
var rf24= new nrf24.nRF24(15,24);
rf24.begin();
// Configure the radio
rf24.config({
  PALevel: nrf24.RF24_PA_LOW
});
 
console.log("write Miousse to channel 0x65646f4e31");

var data=Buffer.from("Miousse"); // Create a node buffer for sending data
rf24.useWritePipe("0x65646f4e31",true); // Select the pipe address to write with Autock
rf24.write(data);

// If you want to abort pending async writes
rf24.stopWrite();