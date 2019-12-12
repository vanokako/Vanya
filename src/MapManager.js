'use strict'

class MapManager {
    constructor() {
        this.currentMap = 0;
        this.mapData      = null; // Информация о карте
        this.tLayer       = null; // Текущий тайл
        this.xCount       = null;
        this.yCount       = null;
        this.imgLoadCount = 0; // количество загруженных изображений
        this.loaded       = false;
        this.tSize        = { x: null, y: null}; //Размер тайла
        this.mapSize      = { x: null, y: null}; // Размер карты
        this.tilesets     = []; // Массив для хранения тайлсетов
        this.view         = { x: 0, y: 0, w: 800, h: 600 }; //Видимая часть
        this.monsters     = 0;
    }

    // отрисовка карты в контексте канваса
    draw(ctx) {
        if(!this.loaded){
            console.log("Not loaded");
            return;

        }
        for (let i = 0; i < this.tLayer.data.length;	i++) { // проходим по всей карте
            if (this.tLayer.data[i] !== 0) { // если данных нет, то пропускае

                let tile = this.getTile(this.tLayer.data[i]); // получение блока по индексу

                let pX = (i % this.xCount) * this.tSize.x; // вычисляем x в пикселях
                let pY = Math.floor(i / this.xCount) * this.tSize.y;
                ctx.drawImage(tile.img, 0, 0, this.tSize.x, this.tSize.y, pX, pY,
                    this.tSize.x, this.tSize.y); //отрисовка в контексте
            }
        }
    }

    isFree(x, y) {
        let tx = Math.floor(x/32),
            ty = Math.floor(y/32)+1;
        return !(this.tLayer.data[tx+this.xCount*ty] == 2);
    }

    isWood(x, y){
        let tx = Math.floor(x/32),
            ty = Math.floor(y/32);
        return !(this.tLayer.data[tx+this.xCount*ty] == 1);
    }

    getTile(tileIndex) {
        let tile = {
            img: null,
            px: 0, py: 0
        };
        let tileset = this.getTileset(tileIndex);
        tile.img = tileset.image;
        let id = tileIndex - tileset.firstgid;
        let x = id % tileset.xCount;
        let y = Math.floor(id / tileset.xCount);
        tile.px = x * this.tSize.x;
        tile.py = y * this.tSize.y;
        return tile; // возвращаем тайл для отображения
    }

    getTileset(tileIndex) {
        for (let i = this.tilesets.length - 1; i >= 0; i--) {
            // в каждом tilesets[i].firstgid записано число, с которого начинается нумерация блоков
            if (this.tilesets[i].firstgid <= tileIndex) {
                // если индекс первого блока меньше, либо равен искомому, значит этот tileset и нужен
                return this.tilesets[i];
            }
        }
        return null;
    }

    load(file) {
        this.loaded = false;
        getReq(file, (req) => {

            mapManager.parseMap(req.response);
            mapManager.parseEntities();
            for (let id = 0; id < mapManager.mapData.layers.length; id++) {
                let layer = mapManager.mapData.layers[id];
                if (layer.type === "tilelayer") {
                    mapManager.tLayer = layer;

                }
            }
            mapManager.loaded = true;

        })

    }

    //Разбираем карту
    parseMap(tilesJSON) {
        this.mapData = JSON.parse(tilesJSON);
        this.xCount = this.mapData.width; // сохранение ширины
        console.log('['+this.xCount+']')
        this.yCount = this.mapData.height; // сохранение высоты
        this.tSize.x = this.mapData.tilewidth; // сохранение размера тайла
        this.tSize.y = this.mapData.tileheight; // сохранение размера тайла
        this.mapSize.x = this.xCount * this.tSize.x; // вычисление размера карты
        this.mapSize.y = this.yCount * this.tSize.y;
        for (let i = 0; i <	this.mapData.tilesets.length; i++) {
            console.log(this.mapData.tilesets[i]);
            let img = new Image(); // создаем переменную для хранения изображений
            img.onload = function () { // при загрузке изображения
                mapManager.imgLoadCount++;

            };
            img.src = "/images/" + this.mapData.tilesets[i].image;
            let t = this.mapData.tilesets[i]; //забираем tileset из карты
            let ts = {
                firstgid: t.firstgid,
                image: img,
                name: t.name, // имя элемента рисунка
                xCount: Math.floor(t.imagewidth / this.tSize.x), // горизонталь
                yCount: Math.floor(t.imageheight / this.tSize.y) // вертикаль
            }; // конец объявления ts
            this.tilesets.push(ts); // сохраняем tileset в массив
            if (mapManager.imgLoadCount === mapManager.mapData.tilesets.length) {
                mapManager.imgLoaded = true;
                if(mapManager.imgLoaded && mapManager.jsonLoaded)
                    mapManager.draw(ctx);
            }
        }
        this.jsonLoaded = true; // когда разобран весь json
    }


    parseEntities() {
        for (let j = 0; j <	this.mapData.layers.length; j++)
            if (this.mapData.layers[j].type === 'objectgroup' ) {
                let entities = this.mapData.layers[j];
                for (let i = 0; i < entities.objects.length; i++) {
                    let e = entities.objects[i];

                    let obj = null;

                    if (e.name == "Player") {
                        obj = new Player({x: e.x, y: e.y}, {x: e.width,y: e.height});
                        gameManager.player = obj;
                    } else if (e.name == "Enemy") {
                        obj = new Enemy({x: e.x, y: e.y}, {x: e.width,y: e.height});
                    }
                    else if (e.name == "Enemy1") {
                        obj = new Enemy1({x: e.x, y: e.y}, {x: e.width,y: e.height});
                    }
                    else if (e.name == "Bonus_OP") {
                        obj = new OP({x: e.x, y: e.y}, {x: e.width,y: e.height});
                    }
                    else if (e.name == "Bonus_Freez") {
                        obj = new Freez({x: e.x, y: e.y}, {x: e.width,y: e.height});
                    }
                    if (obj) {
                        objectManager.addObject(obj);
                    }
                    console.log(obj);
                }
            }
    }
    isFinish(x, y) {
        let tx = Math.floor(x/32),
            ty = Math.floor(y/32)+1;
        return this.tLayer.data[tx+this.xCount*ty] == 4 || this.tLayer.data[tx+this.xCount*ty] == 8;
    }

}

function getReq(url, onsuccess, resType = 'text') {
    let xhr = new XMLHttpRequest();
    xhr.open("GET", url, true);
    if (resType)
        xhr.responseType = resType;
    xhr.onreadystatechange = function() {
        if ((xhr.readyState == 4) && (xhr.status == 200))
            onsuccess(xhr);
    }
    xhr.send();
}

console.log("Loaded MapManager.js")
