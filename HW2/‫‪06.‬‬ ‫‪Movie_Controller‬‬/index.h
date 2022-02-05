const char MAIN_PAGE[] PROGMEM = R"=====( 
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <style>
        @media screen and (max-width: 540px) {
            .view {
                width: 400px;
            }
        }
        body {
            background-color: powderblue;
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: center;
            height: 100vh;
            width: 100vw;

        }
        button, div, #moviename {width: 80%; height: 15%;font-size: 250%;}
        .vol {width: 50%; height: 100%;}
        div,p{display: flex; align-content: center; justify-content: center;}
    </style>
    <title>Document</title>
</head>
<body class="view">
    <button onclick="window.location.href='http://192.168.1.50/play';" id="play" style="background-color:chocolate">Play</button>
    <button id="pause" style="background-color: coral;">Pause</button>
    <div>
        <button id="decreaseVolume" class="vol" style="background-color: darkslateblue; color:antiquewhite">-</button>
        <button id="increaseVolume" class="vol" style="background-color: darkslateblue; color:antiquewhite">+</button>   
    </div>
    <button id="showName" style="background-color: teal;">Name</button>
    <p id="moviename"></p>
</body>
<script>      
    async function play() {                                                
        const response = await fetch('http://192.168.1.50/play', {mode: 'no-cors'});
    }    
    async function pause() {                                                
        const response = await fetch('http://192.168.1.50/pause', {mode: 'no-cors'});
    }    
    async function increaseVolume() {                                                
        const response = await fetch('http://192.168.1.50/increasevolume', {mode: 'no-cors'});
    }                                              
    async function decreaseVolume() {                                                
        const response = await fetch('http://192.168.1.50/decreasevolume', {mode: 'no-cors'});
    }                                              
    async function showName(){
        const response = await fetch('http://192.168.1.50/showname', {mode: 'no-cors'});
        console.log(response)
        let text = await response.text();
        console.log(text)
        document.getElementById("moviename").textContent = text
    }
    document.getElementById("play").onclick = play
    document.getElementById("pause").onclick = pause
    document.getElementById("increaseVolume").onclick = increaseVolume;
    document.getElementById("decreaseVolume").onclick = decreaseVolume;
    document.getElementById("showName").onclick = showName;
</script>   
</html>
)=====";