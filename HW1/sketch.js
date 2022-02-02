let serial;
let portName = 'COM3';
let inData; 
let portSelector;
let powerButton;
let fanSlider;


function preload() {
  img = loadImage('5.png');
}

function setup(event) {
  powerButton = document.getElementById('power');
  powerButton.addEventListener('click', setPowerState);

  fanSlider = document.getElementById('fanSpeed');
  fanSlider.addEventListener('change', setFanSpeed);  
  createCanvas(1000, 1000);
  serial = new p5.SerialPort();
  serial.on('list', printList);
  serial.on('connected', serverConnected); 
  serial.on('open', portOpen);
  serial.on('data', serialEvent); 
  serial.on('error', serialError);
  serial.on('close', portClose); 
  serial.list();
  serial.open(portName); 
  setPowerState();
  setFanSpeed();
}

function setPowerState() {
  // change its value, depending on its current value:
  if (powerButton.value == 'on') {
    powerButton.value = 'off';
  } else {
    powerButton.value = 'on';
  }
  // get the span associated with it and change its text:
  let thisSpan = document.getElementById(powerButton.id + 'Val');
  thisSpan.innerHTML = "Switch is " + powerButton.value;
}

function setFanSpeed(e) {
 // assume e is a number:
var currentValue = e;
// but if it's an object instead, it's because
// the slider change event called this function. 
// Extract the number from it:
  if (typeof e == 'object') {
    currentValue = e.target.value;
  } 
  //get the span associated with it and change its text:
  let thisSpan = document.getElementById(fanSlider.id + 'Val');
  thisSpan.innerHTML ="Now the number is: " + currentValue;
}


function draw() {
   background(255);
   fill(0);
  image(img, 500, 150, inData, inData);
}

function printList(portList) {
  for (var i = 0; i < portList.length; i++) {
    console.log(i + portList[i]);
  }
}

function serverConnected() {
  console.log('connected to server.');
}
 
function portOpen() {
  console.log('the serial port opened.')
}
 
function serialEvent() {
  inData = Number(serial.read());
  setFanSpeed(inData);
}
 
function serialError(err) {
  console.log('Something went wrong with the serial port. ' + err);
}
 
function portClose() {
  console.log('The serial port closed.');
}

