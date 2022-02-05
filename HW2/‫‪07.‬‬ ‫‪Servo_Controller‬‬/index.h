const char MAIN_PAGE[] PROGMEM = R"=====( 
<!DOCTYPE html>
<html>
    <header>
        <meta charset="UTF-8">
        <style>
            body{
                display: flex;
                flex-direction: row;
                align-items: center;
                align-content: center;
                justify-content: center;
            }
        </style>
    </header>
    <body style="display: flex;">


        <label for="vol">0 to 180</label>
        <input type="range" id="degree" name="vol" min="0" max="180">

    </body>
    <script>
        async function changevalue() {                                                
            fetch('http://192.168.4.1/degree', {
                method: 'POST',
                mode: 'no-cors',
                body: document.getElementById("degree").value
            });
        }

        document.getElementById("degree").onchange = changevalue
        document.getElementById("degree").value = 50
    </script>
</html>
)=====";