const gameContainer = document.getElementById('gameContainer');
const playerCar = document.getElementById('playerCar');
const obstacle = document.getElementById('obstacle');
let playerPosition = gameContainer.offsetWidth / 2;

document.addEventListener('keydown', (e) => {
    const containerWidth = gameContainer.offsetWidth;
    const carWidth = playerCar.offsetWidth;

    if (e.key === 'ArrowLeft' && playerPosition > 0) {
        playerPosition -= 10;
        playerCar.style.left = playerPosition + 'px';
    } else if (e.key === 'ArrowRight' && playerPosition < containerWidth - carWidth) {
        playerPosition += 10;
        playerCar.style.left = playerPosition + 'px';
    }
});
