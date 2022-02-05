const char MAIN_PAGE[] PROGMEM = R"=====(
<!DOCTYPE HTML>
<html>
    <head>
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <meta charset="UTF-8">
        <style>
            html {
                font-family: Arial, Helvetica, sans-serif;
                text-align: center;
            }
            h1 {
                font-size: 1.8rem;
                color: white;
            }
            .topnav {
                overflow: hidden;
                background-color: #143642;
            }
            body {
                margin: 0;
            }
            .content {
                padding: 30px;
                max-width: 100%;
                margin: 0 auto;
            }
            .card {
                background-color: #F8F7F9;;
                box-shadow: 2px 2px 12px 1px rgba(140,140,140,.5);
                padding-top:10px;
                padding-bottom:20px;
                width: 90%;
            }
            .ruler, .ruler li {
                margin: 0;
                padding: 0;
                list-style: none;
                display: inline-block;
                width: 100%;
                
            }
            /* IE6-7 Fix */
            .ruler, .ruler li {
                *display: inline;
            }
            .ruler {
                color: #999;
                margin: 0; 
                height: 5em;
                /*padding-right: 1cm;*/
                white-space: nowrap;
                padding-right: 4px;
                
            
              
            }
            .ruler li {
                /*padding-left: 5%;*/
                width: 2em;
                margin: .64em -1em -.64em;
                text-align: center;
                position: relative;
            }
            .ruler li:before {
                content: '';
                position: absolute;
                border-left: 1px solid #999;
                height: .64em;
                top: -.64em;
                right: 1em;
            }
            
            .ruler_wrap{
              padding-left: 10px;
              padding-right: 5px;
                background: linear-gradient(to bottom,  #e2e2e2 0%,#dbdbdb 40%,#d1d1d1 51%,#fefefe 100%);
              border-bottom: 2px solid #aaa;
              border-radius: 5px;
            }
            
            
        </style>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    </head>
    <body>
        <div class="topnav">
            <h1>Distance</h1>
        </div>
        <div class="content">
            <div class="card">
                <!-- <input id="slider" type="range" min="4" max="40" style="width: 90%;"> -->
                <input id="slider" type="range" style="width:100%;" min="3" ng-model="o.q" max="40" step="1" list="L7104240" value=1 class='range'>
                <div class="ruler_wrap">
                    <ul id="ruler" class="ruler" data-items="10"></ul>
                </div>
            </div>
        </div>
    </body>
    <script>
        var gateway = `ws://192.168.1.109/ws`;
        var websocket;
        window.addEventListener('load', onLoad);
        function initWebSocket() {
            console.log('Trying to open a WebSocket connection...');
            websocket = new WebSocket(gateway);
            websocket.onopen    = onOpen;
            websocket.onclose   = onClose;
            websocket.onmessage = onMessage; // <-- add this line
        }
        function onOpen(event) {
            console.log('Connection opened');
        }
        function onClose(event) {
            console.log('Connection closed');
            setTimeout(initWebSocket, 2000);
        }
        function onMessage(event) {
            console.log(parseInt(event.data));
            let val = parseInt(event.data)
            document.getElementById('slider').value = val
        }
        function onLoad(event) {
            initWebSocket();
        }

        var max = 40;
        var step = 3;
        var ruler = document.getElementById('ruler');

        while (ruler.hasChildNodes()) {
            ruler.removeChild(ruler.lastChild);
        }

        var item = document.createElement("li")
        item.style.paddingLeft = (100/max)+"%"

        for (i = 0; i < max; i++) {
        var cl = item.cloneNode(true)
        cl.innerText = i + 1
        ruler.appendChild( cl );
        }

    </script>
</html>
)=====";