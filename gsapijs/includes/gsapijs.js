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
    }
  });
  return result;
}

