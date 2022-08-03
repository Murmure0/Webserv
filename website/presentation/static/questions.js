let last_select = null;

const submit_form = () => {
	const form = document.getElementById("form");
	const input = document.getElementById("answer");
	if (input.type == "file" || input.value != "")
		form.submit();
}

const select_qcm = (elem) => {
	if (last_select == elem)
		return;
	const input = document.getElementById("answer");
	const next_button = document.getElementById("next_button");
	next_button.classList.add("active");
	input.value = elem.getAttribute("answer");
	elem.classList.add("selected");
	if (last_select)
		last_select.classList.remove("selected");
	last_select = elem;
}

const load_listener = () => {
	const input = document.getElementById("answer");
	const next_button = document.getElementById("next_button");
	input.addEventListener("input", (e) => {
		if (e.target.value != "")
			next_button.classList.add("active")
		else
			next_button.classList.remove("active")
	})
}

const setFileDropper = () => {
	const inputElement = document.querySelector("#answer");
	const dropZoneElement = inputElement.closest(".drop-zone");

	dropZoneElement.addEventListener("click", (e) => {
		inputElement.click();
	});

	inputElement.addEventListener("change", (e) => {
		if (inputElement.files.length) {
			for (let index = 0; index < inputElement.files.length; index++) {
				updateThumbnail(dropZoneElement, inputElement.files[index]);
			}
		}
	});

	dropZoneElement.addEventListener("dragover", (e) => {
		e.preventDefault();
		dropZoneElement.classList.add("drop-zone--over");
	});

	["dragleave", "dragend"].forEach((type) => {
		dropZoneElement.addEventListener(type, (e) => {
			dropZoneElement.classList.remove("drop-zone--over");
		});
	});

	dropZoneElement.addEventListener("drop", (e) => {
		e.preventDefault();

		if (e.dataTransfer.files.length) {
			inputElement.files = e.dataTransfer.files;
			for (let index = 0; index < e.dataTransfer.files.length; index++) {
				updateThumbnail(dropZoneElement, e.dataTransfer.files[index]);
			}
		}

		dropZoneElement.classList.remove("drop-zone--over");
	});

}

const clearThumbnail = (dropZoneElement) => {
	dropZoneElement.querySelectorAll(".drop-zone__thumb").forEach((elem) => {
		elem.remove()
	})
}


function updateThumbnail(dropZoneElement, file) {
	const next_button = document.getElementById("next_button");
	if (!next_button.classList.contains("active")) {
		next_button.classList.add("active")
	}
	let thumbnailElement = dropZoneElement.querySelector(".drop-zone__thumb");


	if (dropZoneElement.querySelector(".drop-zone__prompt")) {
		dropZoneElement.querySelector(".drop-zone__prompt").remove();
	}


	thumbnailElement = document.createElement("div");
	thumbnailElement.classList.add("drop-zone__thumb");
	dropZoneElement.appendChild(thumbnailElement);

	thumbnailElement.dataset.label = file.name;


	if (file.type.startsWith("image/")) {
		const reader = new FileReader();

		reader.readAsDataURL(file);
		reader.onload = () => {
			thumbnailElement.style.backgroundImage = `url('${reader.result}')`;
		};
	} else {
		thumbnailElement.style.backgroundImage = null;
	}
}

setFileDropper()