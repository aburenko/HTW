"use strict";

var requestURL = { 
	"treble":"/modules/treble.json",
	"bass":"/modules/bass.json",
	"alto":"/modules/alto.json",
}

var choosenTreble = "treble";
var loadedNotes;
var restNotes;

loadModule(requestURL[choosenTreble]);


function initModule(xhttp) {
	// init gotten module notes to var(arr)
	loadedNotes = JSON.parse(xhttp.responseText);
	// init or reinit array to mark already shown notes
	// any clef has 15 notes
	restNotes = Array.from(Array(15).keys());
}

function nextNote() {
	// pick a random number between 0 and the restNotes length
	var randNum = Math.floor(Math.random() * restNotes.length);
	console.log("randNum: " + randNum);
	// remove that index number from the array
	var roll = restNotes.splice(randNum, 1);
	// clear box and draw next
	clearBox("note");
	console.log("draw: " + choosenTreble + " " + loadedNotes[roll]);
	drawClefKey(choosenTreble, loadedNotes[roll]);
	// check if all notes are showed
	if(restNotes.length == 0)
		document.getElementById("note").innerHTML = "DONE!!!";
}

function loadModule(moduleURL) { 
	// loads module from module URL with AJAX 
	var xhttp = new XMLHttpRequest();
	xhttp.onreadystatechange = function() {
		if (this.readyState == 4 && this.status == 200) {
			// call startModule after recieve
			initModule(this);
		}
	};
	// do asyc GET
	xhttp.open("GET", moduleURL, true);
	xhttp.send();
}

function drawClefKey(clefToDraw, keyToDraw) {
	var VF = Vex.Flow;
	// Create an SVG renderer and attach it to the DIV element named "boo".
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
	  // A quarter-note C.
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