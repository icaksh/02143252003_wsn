<?php
header("Access-Control-Allow-Origin: *");
$hostname = "localhost";
$username = "hanaemim_jsn_user";
$password = "inipassword";
$database = "hanaemim_jsn";

if ($_SERVER['REQUEST_METHOD'] === 'GET') {
    $conn = new PDO("mysql:host=$hostname;dbname=$database", $username, $password);
    $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
    $resultss = array();
    for($i=1; $i<=3; $i=$i+2){
        $sql = "SELECT * FROM gajahduduk_state WHERE id_gate_1 = :gate AND time BETWEEN :start_time AND :end_time ORDER BY time DESC LIMIT 5";
    
        $stmt = $conn->prepare($sql);
        $stmt->bindParam(':end_time', date("Y-m-d H:i:s"));
        $stmt->bindParam(':start_time', date("Y-m-d H:i:s",strtotime("-10 minutes")));
        $stmt->bindParam(':gate', $i);
        
        $stmt->execute();
        
        $results = $stmt->fetchAll(PDO::FETCH_ASSOC);
        array_push($resultss,$results);
    }


    $status = array(
        "data" => $resultss
    );
    http_response_code(200);
    echo json_encode($status);
    exit;
}


try {
    // Connect to the database
    $conn = new PDO("mysql:host=$hostname;dbname=$database", $username, $password);
    $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

    // Receive Arduino data
    $json = file_get_contents('php://input');
    $data = json_decode($json);
    $gate = $data->gate;
    $height = $data->height;
    if(!isset($gate) || !isset($height)){
        $status = array(
            "message" => "harap isi gate and height"
        );
        http_response_code(400);
        echo json_encode($status);
        exit;
    }
    $status = 1;
    if($height > 600){
        $status = 0;
    }
    if($gate == 1){
        $gate_2 =2;
    }elseif($gate ==3){
        $gate_2 = 4;
    }else{
        $status = array(
            "message" => "gate harus bernilai 1 atau 3"
        );
        http_response_code(400);
        echo json_encode($status);
        exit;
    }
    $sql = "INSERT INTO gajahduduk_state (id_gate_1, id_gate_2, time, water_height, status) VALUES (:id_gate_1, :id_gate_2, :time, :water_height, :status)";
    $stmt = $conn->prepare($sql);
    $stmt->bindParam(':id_gate_1', $gate);
    $stmt->bindParam(':id_gate_2', $gate_2);
    $stmt->bindParam(':time', date("Y-m-d H:i:s"));
    $stmt->bindParam(':water_height', $height);
    $stmt->bindParam(':status', $status);

    // Execute the query
    $stmt->execute();
    $status = array(
        "message" => "Data telah tersimpan di database"
    );
    http_response_code(200);
    echo json_encode($status);
    exit;
} catch (PDOException $e) {
    $status = array(
        "message" => $e->getMessage()
    );
    http_response_code(400);
    echo json_encode($status);
    exit;
}
$conn = null;
