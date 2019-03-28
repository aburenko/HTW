"use strict";
drawClefKey("treble", "c/4");


function drawClefKey(clefToDraw, keyToDraw) {
	var VF = Vex.Flow;
	// Create an SVG renderer and attach it to the DIV element named "boo".
	var div = document.getElementById("note")
	var renderer = new VF.Renderer(div, VF.Renderer.Backends.SVG);
	// Size our svg:
	// TODO: ... if render for mobile change size
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
    document.getElementById(elementID).innerHTML = "";
}