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
    $sql = "SELECT * FROM gajahduduk_gate";
    if(isset($_GET['id'])){
        $sql = "SELECT * FROM gajahduduk_gate WHERE id=:id";
    }
    $stmt = $conn->prepare($sql);
    if(isset($_GET['id'])){
        $stmt->bindParam(":id",$_GET['id']);
    }
    $stmt->execute();
    
    
    $results = $stmt->fetchAll(PDO::FETCH_ASSOC);
    
    if(!isset($_GET['id'])){
        $data = array();
        foreach ($results as $index => $row) {
            $rowData = array();
            foreach ($row as $column => $value) {
                $rowData[$column] = $value;
            }
            unset($rowData["id"]);
            $data[$index] = $rowData;
        }
        $status = array(
            "data" => $data
        );
    }else{
        $status = array(
            "data" => $results
        );
    }
    

    
    http_response_code(200);
    echo json_encode($status);
    exit;
}


try {
    $conn = new PDO("mysql:host=$hostname;dbname=$database", $username, $password);
    $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

    $json = file_get_contents('php://input');
    $data = json_decode($json);
    $gate = $data->gate;
    $state = $data->state;
    if(!isset($gate) || !isset($state)){
        $status = array(
            "message" => "harap isi gate and height"
        );
        http_response_code(400);
        echo json_encode($status);
        exit;
    }
    $sql = "UPDATE gajahduduk_gate SET state=:state WHERE id=:gate";
    $stmt = $conn->prepare($sql);
    $stmt->bindParam(':gate', $gate);
    $stmt->bindParam(':state', $state);
    $stmt->execute();
    if ($stmt->rowCount() < 0) {
        $status = array(
            "message" => "Tidak ditemukan"
        );
        http_response_code(404);
        echo json_encode($status);
        exit;
    }
    
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