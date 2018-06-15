<?php
$gmail_user = "user@gmail.com";
$gmail_password = "123456";
$secretKey = "asdfghjkl";
$email_where_notify = "myemail@gmail.com";


ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

use PHPMailer\PHPMailer\PHPMailer;

$secretKey = $_GET["secretKey"];

if($secretKey == $secretKey){

	require_once "PHPMailer/PHPMailer.php";
	require_once "PHPMailer/SMTP.php";
	require_once "PHPMailer/Exception.php";

	$from = 'washing@machine.com';
	$to = $email_where_notify;
	$subject ="Your washing machine has finished!";
	$body ="Hi Samuel,\n\nHow is it going?\nYour pretty washing machine has finished the wash cycle. Please hang clothes and don't be lazy ;)";


	$mail = new PHPMailer;
	$mail->isSMTP();
	$mail->Host = 'smtp.gmail.com';
	$mail->Port = 587;
	$mail->SMTPSecure = 'tls';
	$mail->SMTPAuth = true;
	$mail->Username = $gmail_user;
	$mail->Password = $gmail_password;

	$mail->setFrom($from, 'Washing Machine');
	$mail->addReplyTo($from, 'Washing Machine');
	$mail->addAddress($to);
	$mail->Subject = $subject;
	$mail->Body = $body;

	if (!$mail->send()) {
	    echo "error";
	} else {
	    echo "success";
	}

}else{
	echo "error";
}

?>