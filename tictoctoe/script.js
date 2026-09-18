const cells = [...document.querySelectorAll('.cell')];
const statusText = document.querySelector('#status');
const playerScore = document.querySelector('#player-score');
const computerScore = document.querySelector('#computer-score');
const wins = [[0,1,2],[3,4,5],[6,7,8],[0,3,6],[1,4,7],[2,5,8],[0,4,8],[2,4,6]];
let board = Array(9).fill('');
let scores = { X: 0, O: 0 };
let locked = false;

function winner(state) {
  return wins.find(([a,b,c]) => state[a] && state[a] === state[b] && state[a] === state[c]);
}

function render() {
  cells.forEach((cell, i) => { cell.textContent = board[i]; cell.className = `cell ${board[i].toLowerCase()}`; cell.disabled = locked || board[i] !== ''; });
}

function finish(line, message, winnerMark) {
  locked = true;
  if (line) line.forEach(i => cells[i].classList.add('win'));
  if (winnerMark) scores[winnerMark]++;
  playerScore.textContent = scores.X;
  computerScore.textContent = scores.O;
  statusText.textContent = message;
  render();
}

function evaluate() {
  const line = winner(board);
  if (line) { finish(line, board[line[0]] === 'X' ? 'You win!' : 'CPU wins!', board[line[0]]); return true; }
  if (board.every(Boolean)) { finish(null, 'Draw game'); return true; }
  return false;
}

function cpuMove() {
  const open = board.map((v, i) => v ? null : i).filter(i => i !== null);
  const choice = open[Math.floor(Math.random() * open.length)];
  board[choice] = 'O';
  if (!evaluate()) { locked = false; statusText.textContent = 'Your move'; render(); }
}

function play(index) {
  if (locked || board[index]) return;
  board[index] = 'X';
  if (evaluate()) return;
  locked = true; statusText.textContent = 'CPU is thinking...'; render();
  setTimeout(cpuMove, 430);
}

function reset() { board = Array(9).fill(''); locked = false; statusText.textContent = 'Your move'; render(); }
cells.forEach((cell, i) => cell.addEventListener('click', () => play(i)));
document.querySelector('#reset').addEventListener('click', reset);
render();
