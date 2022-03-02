var mainHeight = function() {
  var total    = $(window).height(),
      $main = $('main').css('height','auto');

  if ($main.outerHeight(true) < total) {
    var margin = $main.outerHeight(true) - $main.height();
    $main.height(total - margin - 20);
  } else {
    $main.css('height','auto');
  }
}

$(window).resize(mainHeight);

$(function() {
  $("main h1, main h2, main h3").each(function(){
    $("nav.nav-left ul").append("<li class='tag-" + this.nodeName.toLowerCase() + "'><a href='#" + $(this).text().toLowerCase().replace(/ /g, '-').replace(/[^\w-]+/g,'') + "'>" + $(this).text() + "</a></li>");
    $(this).attr("id",$(this).text().toLowerCase().replace(/ /g, '-').replace(/[^\w-]+/g,''));
    $("nav.nav-left ul li:first-child a").parent().addClass("active");
  });

  $("nav.nav-left ul li").on("click", "a", function(event) {
    var position = $($(this).attr("href")).offset().top - 190;
    $("html, body").animate({scrollTop: position}, 400);
    $("nav.nav-left ul li a").parent().removeClass("active");
    $(this).parent().addClass("active");
    event.preventDefault();
  });

  mainHeight();

  $('img').on('load', mainHeight);
});
