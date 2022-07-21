

let count = 0;
const count_elem = document.getElementById("count");

setInterval(() => {
	count += 1;
	count_elem.innerHTML = count;
}, 1000);