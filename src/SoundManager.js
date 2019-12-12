'use strict'

class SoundManager {
    constructor() {
        this.audios  = {}; // звуковые эффекты
        this.context = new AudioContext(); // аудиоконтекст
        this.loading = 0; // Количество загружающихся в данный момент звуков
    }
    load(files) {
        console.log("Loading sounds: ", files);
        for(let file of files) {
            getReq(file, (req) => {
                soundManager.context.decodeAudioData(req.response, function(buffer) {
                    soundManager.audios[file] = buffer;
                });
            }, 'arraybuffer');
        }
    }

    play(file, looping = false) {
        let source = this.audios[file];
        if (!source)
            return false;
        // создаем нвоый экземпляр проигрывателя BufferSOurce
        let sound = this.context.createBufferSource();
        sound.buffer = source;
        sound.connect(this.context.destination);
        sound.loop = looping;
        sound.start(0);
        return true;
    }
    stopAll() {
        // for()
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
console.log("Loaded SoundManager.js")
