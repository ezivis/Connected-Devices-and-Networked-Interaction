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
  serial.on('data', serialEvent); 
  serial.list();
  serial.open(portName); 
  
  setPowerState();
  setFanSpeed();
}

function setPowerState() {
  if (powerButton.value == 'on') {
    powerButton.value = 'off';
  } else {
    powerButton.value = 'on';
  }
  let thisSpan = document.getElementById(powerButton.id + 'Val');
  thisSpan.innerHTML = "Switch is " + powerButton.value;
}

function setFanSpeed(e) {
var currentValue = e;
  if (typeof e == 'object') {
    currentValue = e.target.value;
  } 
  //get the span associated with it and change its text:
  let thisSpan = document.getElementById(fanSlider.id + 'Val');
  thisSpan.innerHTML ="Now the number is: " + currentValue;
}

function draw() {
  image(img, 500, 150, inData, inData);
}

function printList(portList) {
  for (var i = 0; i < portList.length; i++) {
    console.log(i + portList[i]);
  }
}
 
function serialEvent() {
  inData = Number(serial.read());
  setFanSpeed(inData);
}
 
