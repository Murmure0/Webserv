

const delete_file = (path) => {
	if (window.confirm("Are you sure you want to delete this file?")) {
		fetch(path, {
			method: 'DELETE'
		});
		setTimeout(() => {
			window.location.reload();
		}, 200);
	}
}