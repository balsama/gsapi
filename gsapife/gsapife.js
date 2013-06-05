$(document).ready(function() {
  /**
   * Stuff in here is only executed on recipe node pages
   */
  if (typeof Drupal.settings.gsapijs != 'undefined') {
    // Highlight the ingredients with promos
    gsapife_highlight_ingredients();

    // Add the tool tip to items with promotions
    $('.has-promos').qtip({
      content: 'Click to See On Sale Ingredients',
      show: { delay: 0 },
      hide: { when: { event: 'unfocus' } },
      position: { corner: { target: 'topRight' } },
      position: { adjust: { x: 5, y: -25 } },
      style: {
        border: { width: 1, radius: 3, color: '#ffd533' },
        tip: { corner: 'leftMiddle' }
      },
      hide: { delay: 100 }
    });

    // On click of a highlighted ingredient
    $('.has-promos').click(function() {
      var delta = $(this).attr('rel');
      gsapife_sip(delta);
    });
  }

  /**
   * Stuff in here is only executed on pages with /recipe in their path
   */
  if ($.inArray('recipes', window.location.pathname.split('/') > -1)) {
    gsapife_find_rwp();
  }

  /**
   * Stuff in here is only executed on the fron page
   */
  if ($('body').hasClass('front')) {
    gsapife_find_rwp();
  }

  /**
   * Find recipes with promotions
   */
  function gsapife_find_rwp() {
    $('.gs-t').each(function() {
      var rid = $(this).children('.field-content').children('span').attr('rel');
      gsapife_highlight_recipes(rid);
    });
  }

  // Update the SL so we can bind the remove click function
  gsapife_update_sl();
  gsapife_wait(false); // So users don't see a wait cursor right off the bat.

  // On click of a remove all link
  $('.sl-remove-all').click(function(e) {
    e.preventDefault();
    gsapife_remove_all();
  });

  // On click of a print button
  $('.sl-print').click(function(e) {
    e.preventDefault();
    gsapife_wait(true);
    gsapife_print();
  });

  // Print any page if param `print` is TRUE
  if (getURLParameter('action', window.location.href) == 'print') {
    window.print();
  }
});

/**
 * Traverses through a recipes ingredients and finds ingredients that have
 * current promotions
 */
function gsapife_highlight_ingredients() {
  var delta = 0;
  $('.recipe-ingredients li').each(function() {
    if (gsapijs_gipc_local(delta) != 0) {
      gsapife_highlight_ingredient(delta);
    }
    delta++;
  });
  return null;
}

/**
 * Adds the promotions `$` to the end of ingredients with promotions
 */
function gsapife_highlight_ingredient(delta) {
  $('.recipe-ingredients li:nth-child(' + (delta + 1) + ')').append('<span class="has-promos item-has-promos" rel="' + delta + '">$</span><span class="element-hidden" id="promo-holder-' + delta + '"></span>');
}

/**
 * Show Item Promotions
 *
 * For a given line item, show promotions in modal after being clicked
 */
function gsapife_sip(delta) {
  $('#promo-holder-' + delta).load(Drupal.settings.basePath + 'gsapife/build_html/promotion?rid=' + Drupal.settings.gsapijs.rid + '&delta=' + delta, function() {
    var items = $('#promo-holder-' + delta).html();
    modalCustom('Promotions', items, '', 'success', 'sl-modal dSuccess');

    // On click of add to shopping list
    $('.add-to-sl').click(function(e) {
      e.preventDefault();
      gsapife_wait(true);
      var promo_id = $(this).attr('rel');
      gsapijs('aip', promo_id);
    });
  });
}

function gsapife_p_remove(pid) {
  gsapijs('rip', pid);
  //gsapife_update_sl();
  gsapife_update_lp();
}

/**
 * Updates the shopping list block with the results of GSL call and binds a
 * click function to the remove button.
 */
function gsapife_update_sl() {
  gsapife_wait(true);
  // Stop auto-resizing so we can animate it once the .load() is complete
  var sidebarHeightOriginal = $('#block-gsapiblocks-gsapiblocks_sl .content').height();
  $('#block-gsapiblocks-gsapiblocks_sl .content').css('height', sidebarHeightOriginal);

  $('#block-gsapiblocks-gsapiblocks_sl .content').load(Drupal.settings.basePath + 'gsapife/build_html/sl', function() {

    // On click of a remove item promotion button
    $('.ip-remove').bind('click', function(e) {
      e.preventDefault();
      var pid = $(this).attr('rel');
      gsapife_p_remove(pid);
    });

    // On click of the sidebar print button
    $('.sl-print-sidebar').click(function(e) {
      e.preventDefault();
      gsapife_print();
    });

    // Animate the height
    $(this).wrapInner('<div/>');
    var newheight = $('div:first',this).height();
    $(this).animate({
      height: newheight,
      complete: gsapife_wait(false),
    });
  });

}

function gsapife_wait(toggle) {
  if (toggle == true) {
    $('body').css('cursor', 'wait');
    $('a').css('cursor', 'not-allowed');
  }
  else {
    $('body').css('cursor', 'inherit');
    $('a').css('cursor', 'inherit');
  }
}

/**
 * Finds recipes with active promotions
 */
function gsapife_highlight_recipes() {
  $('.gs-t').each(function() {
    var rid = $(this).attr('rel');
    if (gsapijs('grpc', rid) != 0) {
      $(this).html('Has Promos!!!');
    }
  });
}

/**
 * async function to get recipe promotion count
 */
function gsapife_highlight_recipes(rid) {
  $.ajax({
    url: Drupal.settings.basePath + 'gsapijs/request/grpc/' + rid,
    type: 'get',
    dataType: 'html',
    success: function(data) {
      gsapife_highlight_recipe(data, rid);
    }
  });
  return null;
}

/**
 * Highlights a given recipe in list view
 */
function gsapife_highlight_recipe(count, rid) {
  if (count != 0) {
    var end = "</div>";
    if (count > 1) {
      end = "s</div>";
    }
    var message = '<div class="r-has-promos"><strong>' + count + '</strong><br />On Sale<br />Ingredient' + end;
    $('#rid-' + rid).parents('.views-field').append(message).click(function() {
      // Send them to the recipe onclick. We'll let the SEO module redirect to the pathurl.
      window.location.href=Drupal.settings.basePath + 'node/' + rid;
    });
  }
}

/**
 * Removes all items from a user's shopping list
 */
function gsapife_remove_all() {
  $.cookie('gsapi_uuid', '', { path: Drupal.settings.basePath });
  gsapife_update_lp();
  gsapife_update_sl();
}

/**
 * Loads the print page in a hidden iframe (in case we're not on that page) and
 * prints the contents of the iframe.
 */
function gsapife_print() {
  $('#sl-print-source').attr('src', Drupal.settings.basePath + 'gsapi/sl-view?action=print');
  setTimeout(gsapife_wait, 2000);
}

function gsapife_update_lp() {
  $('.shopping-list .rows').load(Drupal.settings.basePath + 'gsapife/build_html/sl', function() {
    // On click of a remove item promotion button
    $('.ip-remove').bind('click', function(e) {
      e.preventDefault();
      var pid = $(this).attr('rel');
      gsapife_p_remove(pid);
    });
  });
}
