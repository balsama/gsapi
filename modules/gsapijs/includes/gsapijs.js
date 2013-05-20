/**
 * GS API Shopping List Promotion
 *
 * @param string op
 *   Operation - either add or remove represented as `aip` or `rip`
 * @param int pid
 *   Promotion ID
 *
 * @return object
 *   Object representing users' current SHopping Cart after the Add or Remove
 *   was completed.
 */
function gsapijs_sl_promotion(op, pid) {
  return $.get(Drupal.settings.basePath + 'gsapijs/request/' + op + '/' + pid);
}
