'use strict'

var LEVELS_NUMBER = 2;
class GameManager { // менеджер игры
    constructor() {
        this.player    = null; // указатель на объект игрока
        this.FPS       = 30; // Число кадров в секунду
        this.ctx       = document.getElementById('canvas').getContext('2d');
        this.time      = 0; // Прошедшее время
        this.level     = 1;
        this.updateInterval = null;
        this.minus = 0;
        this.score = 0;
    }
    init() {
        soundManager.load(['/sounds/grassStep.mp3', '/sounds/win.mp3', '/sounds/death.mp3', '/sounds/deadGhost.mp3']);
        mapManager.load("/src/map1.json");
    }
    start() {
        this.init();
        document.getElementById('Level').textContent = '' + this.level + '/' + LEVELS_NUMBER;
        this.updateInterval = setInterval(this.update, 1000/this.FPS);

     }
     update() {
        objectManager.update();
        gameManager.draw();
         let t;
       while(t = eventsManager.popEvent()) {
           gameManager.processEvent(t);
       }
          gameManager.time += 1/gameManager.FPS;
         updateTimer(gameManager.time);
     }

    processEvent(key) {
        switch (key) {
            case 'ArrowLeft':
                this.player.goLeft();
                break;
            case 'ArrowRight':
                this.player.goRight();
                break;
            case 'ArrowUp':
                this.player.goUp();
                break;
            case 'ArrowDown':
                this.player.goDown();
                break;
            default:
                break;
        }
    }

    nextLevel() {
        this.score += this.player.score;
        objectManager.deleteAll();
        soundManager.play('/sounds/win.mp3')
         ++this.level;
         if (this.level <= LEVELS_NUMBER) {
            document.getElementById('Level').textContent = '' + this.level;
             mapManager.load('/src/map' + this.level + '.json');
         }
         else {
             clearInterval(this.updateInterval);
             setTimeout(gameManager.finish, 3000);
         }
    }

    finish(){
        addRecord(gameManager.score);
        document.location.href = '/records';
    }

    draw() {
        let ctx = this.ctx;
        mapManager.draw(this.ctx); // Перерисовываем карту
        objectManager.draw(this.ctx);
    }
}

function updateTimer(secs) {
    let date = new Date(null);
    date.setSeconds(secs);
    let result = date.toISOString().substr(11, 8);
    document.getElementById('Time').textContent = result;
}

function addRecord(score) {
    let username = localStorage.getItem("username");
    let records = localStorage.getItem("records");
    console.log(username)
    if (records) {
        records = JSON.parse(records);
    }
    else {
        records = [];
        let obj = {
            score: score,
            name: username
        };
        records[0] = obj;
        localStorage.setItem("records", JSON.stringify(records));
        return;
    }
    let obj = {
        score: score,
        name: username
    };
    records.push(obj);
    records = records.sort(function (a, b) {
        return b.score- a.score;
    });
    localStorage.setItem("records", JSON.stringify(records));
}

console.log("Loaded GameManager.js")



