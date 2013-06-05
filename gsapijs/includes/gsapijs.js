/**
 * GS API jQuery wrapper
 *
 * @param string op
 *   Operation - one of the following:
 *     - `grd` (Get Recipe Details)
 *     - `grpc` (Get Recipe Promotion Count)
 *     - `gipc` (Get Item Promotion Count - requires args to include delta as: [[rid]|[delta]])
 *     - `aip` (Add Item Promotion)
 *     - `rip` (Remove Item Promotion)
 *     - `gsl` (Get Shopping List)

 * @param mixed args
 *   - integer: Numeric ID of promotion or recipe.
 *   - string: Recipe ID & item delta seperated by a pipe for `gipc` service.
 *
 * @return object
 *   Object representing users' current Shopping Cart after the Add or Remove
 *   was completed.
 *
 * @NOTE Use this method sparingly and only when appropriate. This function is
 *       NOT asyncronous.
 */
function gsapijs(op, args) {
  var result = null;
  $.ajax({
    url: Drupal.settings.basePath + 'gsapijs/request/' + op + '/' + args,
    type: 'get',
    dataType: 'html',
    async: false, // otherwise the callback function would complete before data
                  // was populated
    success: function(data) {
      result = data;
      if ((op == 'aip') || (op == 'rip')) {
        gsapife_update_sl();
      }
    }
  });
  return result;
}

/**
 * Service to return promotion count bt ingredient when recipe details are
 * available in the `Drupal.settings` object. That is, when you are already on
 * a recipe node.
 *
 * @param int delta
 *   The line item of the ingredient (first ingredient = `0`)
 */
function gsapijs_gipc_local(delta) {
  if (typeof Drupal.settings.gsapijs.recipe_details.recipeIngredients[delta].specials != 'undefined') {
    return Drupal.settings.gsapijs.recipe_details.recipeIngredients[delta].specials.length;
  }
  return 0;
}
