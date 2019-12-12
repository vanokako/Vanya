'use strict'

class PhysicsManager {
    constructor() {

    }

    entityAt(x, y, canKill) {
        let objects = [];
        for (var i = 0; i < objectManager.objects.length  ; i++) {
            var e = objectManager.objects[i]; // рассматриваем все объекты на карте

            if (Math.abs(x - e.pos.x) < 10 && Math.abs(y - e.pos.y) < 10 && e.monster == true) {
                objects.push(e); // найден объект
                if(!canKill) {
                    soundManager.play('/sounds/death.mp3');
                    objectManager.deleteAll();
                    setTimeout(this.startGame, 400);
                }
                else {
                    soundManager.play('/sounds/deadGhost.mp3');
                    objectManager.deleteObject(i);
                    gameManager.score += 100;
                }
            }

            if (Math.abs(x - e.pos.x) < 10 && Math.abs(y - e.pos.y) < 10 && e.bonus == true) {
                objectManager.deleteObject(i)
              if (e.bonusID == 1) {
                  gameManager.score += 50;
                  return 1;
              }
              if(e.bonusID == 2){
                  gameManager.score += 50;
                  for (var j = 0; j < objectManager.objects.length  ; j++){
                      var e1 = objectManager.objects[j];
                      if (e1.monster)
                          e1.stop = true;
                  }
              }
            }
        }
    }

    startGame(){
        document.location.href = '/'
    }
}

console.log("Loaded PhysicsManager.js")
