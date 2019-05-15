"use strict";

/* When the user clicks on the button,
toggle between hiding and showing the dropdown content */
function dropdownToggleFunction() {
  document.getElementById("myDropdown").classList.toggle("show");
}

// Close the dropdown menu if the user clicks outside of it
window.onclick = function(event) {
  if (!event.target.matches('.dropbtn')) {
    var dropdowns = document.getElementsByClassName("dropdown-content");
    var i;
    for (i = 0; i < dropdowns.length; i++) {
      var openDropdown = dropdowns[i];
      if (openDropdown.classList.contains('show')) {
        openDropdown.classList.remove('show');
      }
    }
  }
} 

var requestURL = { 
	"treble":"/modules/treble.json",
	"bass":"/modules/bass.json",
	"alto":"/modules/alto.json",
}

var notesPossibilities = {
	"A":1, "B":2, "C":3,
	"D":4, "E":5, 
	"F":6, "G":7
};

var chosenClef = "treble";
var loadedNotes;
var restNotes;
// vars for statistics
var answered = 0;
var answeredRight = 0;
var answeredRightBest = 0; /* Best score */

loadModule(chosenClef);

/*Chosen answer-button function*/
function decisionButton(buttonNumber) {
	// after any decicision block all buttons
	enableButtons(false);
	// get answer and compare it
	var button = document.getElementById("decisionButton" + buttonNumber);
	var answer = button.innerHTML;
	var correct = rightAnswer === answer;
	// repaint progress bars
	if(correct) {
		answeredRight++;
		drawProgressBar(answeredRight, 15, "progressBar");
	} 
	answered++;
	drawProgressBar(answered, 15, "progressBarGeneral");
	// mark the righth button
	var buttonRight = document.getElementById("decisionButton" + rightAnswerIndex);
	buttonRight.style.background = "#33cc33";
	console.log("decisionButton" + rightAnswerIndex);
	// check if all notes are showed
	if(restNotes.length == 0) {
		console.log("module end");
		// TODO: at the end notify user to choose next module
		return;
	}
	// turn button on
	toggleButton("next");
}

function drawProgressBar(part, full, id) {
	// calc percent of progress
	try {
		var percent = Math.ceil(part/full*100);
	} catch (nullException) { 
		console.exception(nullException);
		return; 
	}
	var elem = document.getElementById(id);   
	// get curr width and split it until % to get number
	var width = elem.style.width.split('%')[0];
	var id = setInterval(frame, 10);
	function frame() {
		if (width >= percent) {
			clearInterval(id);
		} else {
			width++; 
			elem.style.width = width + '%'; 
			elem.innerHTML = width * 1  + '%';
		}
	}
}

function resetProgressBar(id) {
	var elem = document.getElementById(id);   
	// reset width of progress bar elem
	elem.style.width = "0%"; 
	elem.innerHTML = "0%";
}

// reset to first color value
function rePaintButtons() {
	var button;
	for(var i=1; i<=4; i++) {
		button = document.getElementById("decisionButton" + i);
		button.style.background = "#4CAF50"; 
	}
}

// enables or disables buttons
function enableButtons(status) {
	var button;
	for(var i=1; i<=4; i++) {
		button = document.getElementById("decisionButton" + i);
		if(!status) button.onclick = null;
		else {
			switch(i) {
				case 1: button.onclick = function() {decisionButton(1)};
					break;
				case 2: button.onclick = function() {decisionButton(2)};
					break;
				case 3: button.onclick = function() {decisionButton(3)};
					break;
				case 4: button.onclick = function() {decisionButton(4)};
					break;
				default: throw "wrong button id";
			}
		}
	}
}

/*Function of chosen module in the dropdown menu*/
function loadModule(clef) {
	chosenClef = clef;
	var moduleURL = requestURL[clef];
	// loads module from module URL with AJAX 
	var xhttp = new XMLHttpRequest();
	xhttp.onreadystatechange = function() {
		if (this.readyState == 4 && this.status == 200) {
			// call startModule after recieve
			console.log("loaded module: " + clef);
			initModule(this);
		}
	};
	// do asyc GET
	xhttp.open("GET", moduleURL, true);
	xhttp.send();
}

function initModule(xhttp) {
	resetStatistics();
	resetProgressBar("progressBar");
	resetProgressBar("progressBarGeneral");
	// init gotten module notes to var(arr)
	loadedNotes = JSON.parse(xhttp.responseText);
	// init or reinit array to mark already shown notes
	// any clef has 15 notes
	restNotes = Array.from(Array(15).keys());
	nextNote();
	// set next button to disabled
	document.getElementById("next").disabled = true;
}

function nextNote() {
	// turn button off
	toggleButton("next");
	// pick a random number between 0 and the restNotes length
	var randNum = Math.floor(Math.random() * restNotes.length);
	// remove that index number from the array
	var roll = restNotes.splice(randNum, 1);
	// clear box and draw next
	clearBox("note");
	console.log("draw: " + chosenClef + " " + loadedNotes[roll]);
	drawClefKey(chosenClef, loadedNotes[roll]);
	enableButtons(true);
	rePaintButtons();
	initButtons(loadedNotes[roll]);
}

var rightAnswer;
var rightAnswerIndex;
var notesPossibilities = {
	0:"A", 1:"B", 2:"C",
	3:"D", 4:"E", 
	5:"F", 6:"G"
};
function initButtons(chosenNote) {
	chosenNote = chosenNote.slice(0,1);
	rightAnswer = chosenNote;
	// create array for filled buttons
	var buttonsStatus = [1, 2, 3, 4];
	var notesPossArr = [0, 1, 2, 3, 4, 5, 6];
	// remove from possible notes
	var chosenNoteNum = getKeyByValue(notesPossibilities, chosenNote);
	notesPossArr.splice(chosenNoteNum, 1);
	// choose random button to fill and cut from array
	var randNum = Math.floor(Math.random() * 4);
	var buttonNum = buttonsStatus.splice(randNum, 1);
	// fill array
	document.getElementById("decisionButton" + buttonNum).innerHTML = chosenNote;
	rightAnswerIndex = buttonNum;

	// fill another buttons
	for (var i = 3; i > 0; i--) {
		// choose random button to fill and cut from array
		randNum = Math.floor(Math.random() * i);
		buttonNum = buttonsStatus.splice(randNum, 1);
		// choose random note for filling and cut from array
		randNum = Math.floor(Math.random() * notesPossArr.length);
		var note = notesPossibilities[notesPossArr.splice(randNum, 1)];
		// fill
		document.getElementById("decisionButton" + buttonNum).innerHTML = note;
	};
}

function drawClefKey(clefToDraw, keyToDraw) {
	var VF = Vex.Flow;
	// Create an SVG renderer and attach it to the DIV element named "note".
	var div = document.getElementById("note")
	var renderer = new VF.Renderer(div, VF.Renderer.Backends.SVG);
	// Size our svg:
	// TODO: ... if render for mobile -> change size
	renderer.resize(250, 250);
	// And get a drawing context:
	var context = renderer.getContext();
	// Create a stave at position 10, 40 of width 400 on the canvas.
	var stave = new VF.Stave(10, 40, 400);
	// Add a clef and time signature.
	stave.addClef(clefToDraw);
	// Connect it to the rendering context and draw!
	stave.setContext(context).draw();
	var notes = [
	  // create a given note for drawing.
	  new VF.StaveNote({clef: clefToDraw, keys: [keyToDraw],
		duration: "q", auto_stem: true })
	];
	// Create a voice in 4/4 and add above notes
	var voice = new VF.Voice({num_beats: 1,  beat_value: 4});
	voice.addTickables(notes);
	// Format and justify the notes to 400 pixels.
	var formatter = new VF.Formatter().joinVoices([voice]).format([voice], 400);
	// Render voice
	voice.draw(context, stave);
}

function clearBox(elementID)
{
	// clears given box with elementID
    document.getElementById(elementID).innerHTML = "";
}

// returns name of key from object by value
function getKeyByValue(object, value) {
	return Object.keys(object).find(key => object[key] === value);
}

// resets statistics
function resetStatistics() {
	answeredRight = 0;
	answered = 0;
}

// toggles enable value of button with ID
function toggleButton(ID) {
	var button = document.getElementById(ID);
	var value = button.disabled;
	button.disabled = !(value);
}