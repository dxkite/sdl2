/*
*  SDL2教程网页组件
*  7月11日 2015
*  © DXkite
*/
function addCssByLink(url)
{

    var doc = document;
    var link = doc.createElement("link");
    link.setAttribute("rel", "stylesheet");
    link.setAttribute("type", "text/css");
    link.setAttribute("href", url);
    
    var heads = doc.getElementsByTagName("head");
    if (heads.length)
        heads[0].appendChild(link);
    else
        doc.documentElement.appendChild(link);
		//alert(url);
}
function showIMG(url)
{
	// alert(url);
	event.cancelBubble = true;
	var img_view = document.getElementById("img_view");
	img_view.style.display = "block";
	var img_show = document.getElementById("img_show");
	img_show.src = url;

}

function add_event(Obj)
{
	Obj.onclick = function()
	{
		showIMG(Obj.attributes.getNamedItem("src").nodeValue);
	}
}

function addImgPop()
{

	var imgs = document.getElementsByTagName("img");
	for (i = 0; i < imgs.length - 1; i++)
	{
		var show;
		if (imgs[i].className == "scr_shoot")
		{
			add_event(imgs[i]);
		}
	}
}


function load()
{
	// var computer = document.getElementById("computer");
	// var phone = document.getElementById("phone");
	var menu = document.getElementById("menu");
	var ctrl_menu = document.getElementById("ctrl_menu");

	if (window.innerWidth < 800)
    {
       // phone.style.display = "block";
        addCssByLink("./common/css/phone-styles.css");
		addImgPop();
    }
    else
    {
      //  computer.style.display = "block";
        addCssByLink("./common/css/pc-styles.css");
        
    }


	ctrl_menu.onclick = function()
	{
		event.cancelBubble = true;
		// alert(imgs.length);
		if (menu.style.display == "none")
		{

			menu.style.display = "block";

		}
		else
		{
			menu.style.display = "none";

		}

	}
	window.onclick = function()
	{
		menu.style.display = "none";
		document.getElementById("img_view").style.display = "none";
	}
		if (loading&&loaded)
	{
	loaded.style.display = "block";
	loading.style.display ="none";
	}
}

window.onload = load;
