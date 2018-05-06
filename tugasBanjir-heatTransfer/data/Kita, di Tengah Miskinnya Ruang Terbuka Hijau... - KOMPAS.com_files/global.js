/**
 * We use the initCallback callback
 * to assign functionality to the controls
 */
function mycarousel_initCallback(carousel) {

    jQuery('#mycarousel-next').bind('click', function() {
        carousel.next();
        return false;
    });

    jQuery('#mycarousel-prev').bind('click', function() {
        carousel.prev();
        return false;
    });
};

// Ride the carousel...
jQuery(document).ready(function() {
    jQuery("#mycarousel").jcarousel({
        scroll: 1,
        initCallback: mycarousel_initCallback,
        // This tells jCarousel NOT to autobuild prev/next buttons
        buttonNextHTML: null,
        buttonPrevHTML: null
    });
});

function mycarousel2_initCallback(carousel) {
   

    jQuery('#mycarousel2-next').bind('click', function() {
        carousel.next();
        return false;
    });

    jQuery('#mycarousel2-prev').bind('click', function() {
        carousel.prev();
        return false;
    });
};
jQuery(document).ready(function() {
    jQuery("#mycarousel2").jcarousel({
        scroll: 1,
        initCallback: mycarousel2_initCallback,
        // This tells jCarousel NOT to autobuild prev/next buttons
        buttonNextHTML: null,
        buttonPrevHTML: null
    });
});