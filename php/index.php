<?php
#作者:小爬虫 网址：www.xiaopachong
date_Default_TimeZone_set("PRC");
require_once("fun.php");
require_once("config.php");

$biaoti = $_POST['biaoti'];
$neirong = $_POST['neirong'];
$touxiang = $_POST['touxiang'];
$nicheng = $_POST['nicheng'];
$page = $_GET['page'];
//插入数据库
if($biaoti)
{
	$time = time();
	$sql = "insert into lyb set biaoti='$biaoti',neirong='$neirong',touxiang='$touxiang',time='$time',nicheng='$nicheng'";
	mysql_query("SET NAMES 'utf-8'"); 
 	$rs = mysql_query($sql);
	if($rs)
	{
		echo "<meta http-equiv=refresh content='0; url=index.php'>"; 

	}
}

//删除留言
if($_GET['pd']=='del')
{
	$id = $_GET['id'];
	$sql = "delete from lyb where id='$id'";
		mysql_query("SET NAMES 'utf-8'"); 
	$rs = mysql_query($sql);
    if($rs)
	{
		echo "<meta http-equiv=refresh content='0; url=index.php'>"; 

	}
}
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312" />
<link id="MainCss" type="text/css" rel="stylesheet" href="./css/css.css"/>
<title>小爬虫留言板</title>
<style type="text/css">
<!--
.STYLE1 {
	font-size: 18px;
	font-weight: bold;
}
-->
</style>
<script language="javascript" type="text/javascript">
function dosubmit()
{
	 if(document.form1.biaoti.value =='')
	 {
	   alert("标题不能为空");
	   document.form1.biaoti.focus();
	   
	  return false;
	 }
	 if(document.form1.neirong.value =='')
	 {
	  alert("内容不能为空");
	  document.form1.neirong.focus();
	   return false;
	 }
	 return true;

}
</script>
</head>

<body>
<table width="800" border="0" align="center" cellspacing="1" bgcolor="#DDE4F4" onsubmit="return dosubmit();">
  <tr>
    <td height="50" colspan="2" align="center" bgcolor="#CCCFEC"><span class="STYLE1">小爬虫留言板</span></td>
  </tr>
  <tr>
    <td height="25" colspan="2" bgcolor="#FFFFFF">&nbsp;</td>
  </tr>
  <tr>
    <td height="25" colspan="2" bgcolor="#EDEEF8">&nbsp;留言列表</td>
  </tr>
  <?php
  //列表
   $sql = "select * from lyb order by id desc";
   	mysql_query("SET NAMES 'utf-8'"); 

   $rs = mysql_query($sql);
  if($rs)
  {
	  $num = mysql_num_rows($rs);
  }

  $page_size = 3; //每页显示数目更改

  $sql = "select * from lyb order by id desc ".get_limit($page_size);
  	mysql_query("SET NAMES 'utf-8'"); 
  $rs = mysql_query($sql);

  if($rs)
  {
  while($rows = mysql_fetch_object($rs))
  {
  ?>
  <tr>
    <td width="167" height="25" bgcolor="#FFFFFF">
      <table width="100%" height="100%" border="0">
        <tr>
          <td align="center"><img src="images/<?=$rows->touxiang?>.gif"   border="0" /></td>
        </tr>
        <tr>
          <td align="center"><?=$rows->nicheng?></td>
        </tr>
      </table></td>
    <td width="726" height="25" valign="middle" bgcolor="#FFFFFF">
      <table width="100%" border="0" cellspacing="1" bgcolor="#EAEAEA">
      <tr>
        <td height="30" bgcolor="#FFFFFF">&nbsp;时间：<?php echo date( "Y-m-d H:i:s",$rows->time);  ?>&nbsp;&nbsp;主题：<?=$rows->biaoti?></td>
      </tr>
      <tr>
        <td height="30" bgcolor="#FFFFFF">&nbsp;<?=$rows->neirong?></td>
      </tr>
      <tr>
        <td height="30" bgcolor="#FFFFFF"><a href='?pd=del&id=<?=$rows->id?>'>&nbsp;删除</a></td>
      </tr>
    </table></td>
  </tr>
  <?php
  }}
  ?>
  <tr>
    <td height="25" colspan="2" align="center" bgcolor="#EDEEF8"><?php echo get_page_list("index.php",$num,$page_size,5); ?></td>
  </tr>
</table>
<br />
<form action='' method='post' id="form1" name="form1" onsubmit="return dosubmit();">
<table width="800" border="0" align="center" cellspacing="1" bgcolor="#E1D1BF">
  <tr>
    <td   height="25" colspan="2" align="left" bgcolor="#E1D1BF">&nbsp;发布留言</td>
  </tr>
  <tr>
    <td width="123"   height="25" align="center" bgcolor="#FFFFFF">标题</td>
    <td bgcolor="#FFFFFF"><input name="biaoti" type="text" size="40" />&nbsp;*</td>
  </tr>
  <tr>
    <td height="25" align="center" bgcolor="#FFFFFF">留言内容</td>
    <td bgcolor="#FFFFFF"><textarea name="neirong" cols="55" rows="8"></textarea>      
    &nbsp;*</td>
  </tr>
  <tr>
    <td height="25" align="center" bgcolor="#FFFFFF">昵称</td>
    <td bgcolor="#FFFFFF"><input name="nicheng" type="text" size="40" /></td>
  </tr>
  <tr>
    <td height="60" align="center" bgcolor="#FFFFFF">选择头像</td>
    <td height="30" bgcolor="#FFFFFF">
	&nbsp;<input name="touxiang" type="radio" value="01" checked="checked" />
    &nbsp;<img src="images/01.gif" width="30" height="30" border="0" />
	&nbsp;<input type="radio" name="touxiang" value="02" />
	&nbsp;<img src="images/02.gif" width="30" height="30" border="0" />
	&nbsp;<input type="radio" name="touxiang" value="03" />
	&nbsp;<img src="images/03.gif" width="30" height="30" border="0" />
	&nbsp;<input type="radio" name="touxiang" value="04" />
	&nbsp;<img src="images/04.gif" width="30" height="30" border="0"  />
	&nbsp;<input type="radio" name="touxiang" value="05" />
	&nbsp;<img src="images/05.gif" width="30" height="30" border="0" />&nbsp;    </td>
  </tr>
  <tr>
    <td height="35" colspan="2" align="center" bgcolor="#FFFFFF"><input type="submit" name="Submit" id="button" value="提交"   />&nbsp;&nbsp;
    <input type="reset" name="Submit2" value="重置" /></td>
  </tr>
</table>
</form>
<br />
<table width="800" border="0" align="center">
  <tr>
    <td height="30" align="center" bgcolor="#CCCFEC">作品:<a href="http://www.xiaopachong.com" target="_blank">小爬虫</a> 网址：<a href="http://www.xiaopachong.com" target="_blank">www.xiaopachong.com</a></td>
  </tr>
</table>
</body>
</html>
