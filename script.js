let puzzle = document.getElementById("puzzle");

let numbers = [1, 2, 3, 4, 5, 6, 7, 8, ""];

function draw() {
    puzzle.innerHTML = "";
    numbers.forEach((num, index) => {
        let div = document.createElement("div");
        div.className = "tile";
        if (num === "") div.classList.add("empty");
        div.innerText = num;
        div.onclick = () => move(index);
        puzzle.appendChild(div);
    });
}

function move(index) {
    let emptyIndex = numbers.indexOf("");
    let validMoves = [
        emptyIndex - 1,
        emptyIndex + 1,
        emptyIndex - 3,
        emptyIndex + 3
    ];

    if (validMoves.includes(index)) {
        [numbers[index], numbers[emptyIndex]] =
        [numbers[emptyIndex], numbers[index]];
        draw();
        checkWin();
    }
}

function shuffle() {
    numbers.sort(() => Math.random() - 0.5);
    draw();
}

function checkWin() {
    let win = [1,2,3,4,5,6,7,8,""].toString();
    if (numbers.toString() === win) {
        alert("🎉 Puzzle Solved!");
    }
}

draw();
