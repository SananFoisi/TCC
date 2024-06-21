<!DOCTYPE HTML>
<html>
<head>
  <style>
    body {
      font-family: Arial, sans-serif;
      margin: 0;
      padding: 0;
      display: flex;
      justify-content: center;
      align-items: center;
      height: 100vh;
      background-color: #f0f0f0;
    }
    .container {
      text-align: center;
      background: #fff;
      padding: 20px;
      border-radius: 8px;
      box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
    }
    h1 {
      margin-bottom: 20px;
      color: #333;
    }
    .button {
      display: inline-block;
      padding: 10px 20px;
      margin: 10px;
      font-size: 16px;
      color: #fff;
      background-color: #007bff;
      border: none;
      border-radius: 4px;
      text-decoration: none;
      cursor: pointer;
      transition: background-color 0.3s;
    }
    .button:hover {
      background-color: #0056b3;
    }
  </style>
</head>
<body>
  <div class="container">
    <h1>Controle de Relés</h1>
    <a href="/relay1/on" class="button">Relé 1 ON</a>
    <a href="/relay1/off" class="button">Relé 1 OFF</a>
    <!-- Adicionar botões para outros relés -->
    <h1>Temperatura: <span id="temperature">--</span>°C</h1>
    <h1>Sensores LDR</h1>
    <p>Sensor LDR 1: <span id="ldr1">--</span>%</p>
    <p>Sensor LDR 2: <span id="ldr2">--</span>%</p>
    <p>Sensor LDR 3: <span id="ldr3">--</span>%</p>
    <h1>Status da Chuva: <span id="rainStatus">--</span></h1>
  </div>
</body>
</html>
