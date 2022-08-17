

const canvas = document.getElementById("main_canvas");
const context = canvas.getContext('2d');

const span_player_score = document.getElementById("player_score");
const span_computer_score = document.getElementById("computer_score");

const players_move = 10;
const ball_speed = 12;
const interval = 30;
const ball_x_start = 350;
const ball_y_start = 250;

const players_start = 230;

const draw_game = (context, player1_y, player2_y, ball_x, ball_y) => {
	context.clearRect(-100, -100, context.canvas.width + 100, context.canvas.height + 100);
	context.fillStyle = '#CB4335';
	context.fillRect(ball_x - 5, ball_y - 5, 10, 10);
	context.fill();
	context.fillStyle = '#00BFA6';
	context.fillRect(10, player1_y, 10, 60);
	context.fillRect(context.canvas.width - 20, player2_y, 10, 60);
}

const getRandomInt = (max) => {
	return Math.floor(Math.random() * max);
}

const random_ball = () => {
	return Math.random() * Math.PI / 2 - Math.PI / 4 + getRandomInt(2) * Math.PI;
}

const touch_player = (player, player_y, computer_y, ball_angle) => {
	const x = player == "player" ? 0 : 670;
	const c_pos = player == "player" ? player_y : computer_y;
	const abstract = ball_angle < Math.PI / 2;
	if (abstract && player == "player") {
		return false;
	}

	if (!abstract && player == "computer") {
		return false;
	}

	return (ball_x >= x && ball_x <= x + 30) && (ball_y >= c_pos && ball_y <= c_pos + 70);
}

const move_ball = () => {
	ball_x += ball_speed * Math.cos(ball_angle);
	ball_y += ball_speed * Math.sin(ball_angle);

	if (ball_x > 700) {
		ball_x = ball_x_start;
		ball_y = ball_y_start;
		ball_angle = random_ball();
		player_score += 1;
		span_player_score.innerHTML = player_score;
	} else if (ball_x < 0) {
		ball_x = ball_x_start;
		ball_y = ball_y_start;
		ball_angle = random_ball();
		computer_score += 1;
		span_computer_score.innerHTML = computer_score;
	}
	if (ball_y >= 495) {
		ball_angle = -ball_angle;
	} else if (ball_y <= 5) {
		ball_angle = -ball_angle;
	}
}

const computer_move = (computer_y, ball_y) => {
	let move = Math.abs(computer_y + 30 - ball_x);
	if (move > 10) {
		move = 10;
	}

	if (ball_y > computer_y && ball_y < computer_y + 60)
		move = 0;
	let y = ball_y > computer_y + 30 ? computer_y + move : computer_y - move;

	if (y < 10)
		y = 10;
	if (y > 430)
		y = 430;
	return y;
}

let player_y = players_start;
let player_move = "n";
let computer_y = players_start;
let ball_angle = random_ball();
let ball_x = ball_x_start;
let ball_y = ball_y_start;
let player_score = 0;
let computer_score = 0;

draw_game(context, player_y, computer_y, 350, 250);

window.addEventListener("keyup", (key_e) => {
	if (key_e.key == "ArrowUp" && player_move == "u") {
		player_move = "n";
	}
	else if (key_e.key == "ArrowDown" && player_move == "d") {
		player_move = "n";
	}
})

window.addEventListener("keydown", (key_e) => {
	if (key_e.key == "ArrowUp") {
		player_move = "u";
	}
	else if (key_e.key == "ArrowDown") {
		player_move = "d";
	}
})

const loop = () => {
	player_y += player_move == "n" ? 0 : player_move == "u" ? -players_move : players_move;
	if (player_y < 10)
		player_y = 10;
	if (player_y > 430)
		player_y = 430;
	computer_y = computer_move(computer_y, ball_y);
	move_ball();
	if (touch_player("player", player_y, computer_y, ball_angle)) {
		ball_angle = Math.PI - ball_angle;
	}
	if (touch_player("computer", player_y, computer_y, ball_angle)) {
		ball_angle = Math.PI - ball_angle;
	}
	draw_game(context, player_y, computer_y, ball_x, ball_y);
}

setInterval(() => {
	loop();
}, interval);
