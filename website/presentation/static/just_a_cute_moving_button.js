

const button = document.getElementById("rage_click_button");

const height = window.innerHeight - 50;
const width = window.innerWidth - 100;

let font_size = 12;

let list = true;

const rand = () => {
	font_size += (font_size / 10) < 1 ? 1 : Math.floor(font_size / 10);
	button.style.fontSize = font_size.toString() + "px";
	let randH = Math.floor(Math.random() * (height)) + 20;
	let randW = Math.floor(Math.random() * width) + 20;
	if (height - randH < button.offsetHeight) {
		randH -= (button.offsetHeight - (height - randH) + 20);
	}
	if (width - randW < button.offsetWidth) {
		randW -= (button.offsetWidth - (width - randW) + 20);
	}
	button.style.top = randH.toString() + "px";
	button.style.left = randW.toString() + "px";
}

button.addEventListener("mouseover", rand);

const easter_egg = () => {
	if (list) {
		list = false;
		button.removeEventListener("mouseover", rand);
	}
}

const open_easter = () => {
	window.location.href = "https://www.youtube.com/watch?v=dQw4w9WgXcQ";
}