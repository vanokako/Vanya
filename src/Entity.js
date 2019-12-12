'use strict'

class Entity {
    constructor(pos = {x: 0, y: 0}, size = {x: 0, y: 0}) {
        this.pos   = {};
        this.pos.x = pos.x;
        this.pos.y = pos.y;
        this.sprite = new Image();
        this.monster = true;
        this.bonus = false;
    }
    draw(ctx) {
        ctx.drawImage(this.sprite, this.pos.x, this.pos.y);
    }
    update() { }
    goUp() {
        let x = this.pos.x,
            y = this.pos.y - 32;
        if (mapManager.isFree(x, y)) {
            this.pos.y = y;
        }
    }
    goDown() {
        let x = this.pos.x,
            y = this.pos.y + 32;
        if (mapManager.isFree(x, y)) {
            this.pos.y = y;

        }
    }
    goRight() {
        let x = this.pos.x + 32,
            y = this.pos.y;
        if (mapManager.isFree(x, y)) {
            this.pos.x = x;

        }
    }
    goLeft() {
        let x = this.pos.x - 32,
            y = this.pos.y;
        if (mapManager.isFree(x, y)) {
            this.pos.x = x;

        }
    }
};

class Player extends Entity {
    constructor(pos = {x: 0, y: 0}, size = {x: 0, y: 0}) {
        console.log("CONSTRUCTING PLAYER");
        super(pos, size);
        this.monster = false;
        this.sprite.src = '/images/12.png';
        this.canKill = false;
        this.score = 1000;
        this.minus = 0;
    }
     update() {
         if (mapManager.isFinish(this.pos.x, this.pos.y)) {
             gameManager.nextLevel();
         }
         if(physicsManager.entityAt(this.pos.x, this.pos.y, this.canKill) == 1){
             this.canKill = true;
         }

         if(this.minus != 30) {
             this.minus++;
             return
         }
         this.minus = 0;
         if(this.score)
             this.score -= 10

         console.log(this.score);
     }

     goUp() {
         super.goUp();
         soundManager.play('/sounds/grassStep.mp3')
         if(!this.canKill)
            this.sprite.src = '/images/13.png';
         else
             this.sprite.src = './images/op4.png'
     }

     goLeft() {
         super.goLeft();
         soundManager.play('/sounds/grassStep.mp3')
         if(!this.canKill)
            this.sprite.src = '/images/14.png';
         else
             this.sprite.src = './images/op2.png'
     }

     goDown() {
         super.goDown();
         soundManager.play('/sounds/grassStep.mp3')
         if(!this.canKill)
             this.sprite.src = '/images/12.png';
         else
             this.sprite.src = './images/op1.png'
     }

     goRight() {
         super.goRight();
         soundManager.play('/sounds/grassStep.mp3')
         if(!this.canKill)
             this.sprite.src = '/images/15.png';
         else
             this.sprite.src = './images/op3.png'
     }


};

class Enemy extends Entity {
    constructor(pos = {x: 0, y: 0}, size = {x: 0, y: 0}) {
        super(pos, size);
        this.sprite.src = '/images/Enemy.png';
        this.timer = 0;
        this.stop = false;
        this.stopTimer = 0;
    }

     update() {
         if (this.stop){
             ++this.stopTimer;
             if(this.stopTimer != 300)
                 return;
             this.stop = false;
             this.stopTimer = 0;
         }
         ++this.timer;
         if(this.timer != 15)
             return;
         this.timer = 0;
         let tmp = null;
         while (!tmp) {
             if (Math.floor(Math.random()*10)%2) {
                 if (Math.floor(Math.random()*10)%2) {
                     if (mapManager.isFree(this.pos.x+32, this.pos.y))
                         tmp = 1;
                 } else {
                     if (mapManager.isFree(this.pos.x-32, this.pos.y))
                         tmp = 2;
                 }
             } else {
                 if (Math.floor(Math.random()*10)%2) {
                     if (mapManager.isFree(this.pos.x, this.pos.y+32))
                         tmp = 3;
                 } else {
                     if (mapManager.isFree(this.pos.x, this.pos.y-32))
                         tmp = 4;
                 }
             }
         }
         if (tmp == 1)
             this.pos.x += 32;
         else if (tmp == 2)
             this.pos.x -= 32;
         else if (tmp == 3)
             this.pos.y += 32;
         else if (tmp == 4)
             this.pos.y -= 32;
     }

}

class Enemy1 extends Enemy{
    constructor(pos = {x: 0, y: 0}, size = {x: 0, y: 0}) {
        super(pos, size);
        this.sprite.src = '/images/Enemy1.png';
    }
    update() {
        super.update();
    }
}


class OP extends Entity{
    constructor(pos = {x: 0, y: 0}, size = {x: 0, y: 0}) {
        super(pos, size);
        this.monster = false;
        this.bonus = true;
        this.bonusID = 1;
        this.sprite.src = '/images/OP_bonus.png';
    }

}

class Freez extends Entity{
    constructor(pos = {x: 0, y: 0}, size = {x: 0, y: 0}) {
        super(pos, size);
        this.monster = false;
        this.bonus = true;
        this.bonusID = 2;
        this.sprite.src = '/images/freez.png';
    }

}
console.log("Loaded Entities.js")
