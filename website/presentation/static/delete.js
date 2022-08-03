

const delete_file = (path) => {
	fetch(path, {
		method: 'DELETE'
	});
	window.location.reload();
}