<?php
/**
 * Available variables:
 *   -$items
 *     Object containing promotions
 */
?>

<?php $count = count($items); ?>
<?php for ($i=0;$i<$count;$i++) : ?>
  <?php $zebra = ($i%2) ? 'even' : 'odd'; ?>
  <?php $item =  $items[$i]; ?>
  <div class="row row-<?php print $i+1; ?> row-<?php print $zebra; ?> clearfix">
    <div class="image promo-item-image">
      <?php print theme('image', $item->imageUrl, '', '', array('width' => 50, 'height' => 50), FALSE); ?>
    </div>
    <div class="promo-item-details clearfix">
      <div class="promo-item-title">
        <?php print $item->defaultDisplayDescription; ?>
      </div>
      <div class="promo-item-savings">
        <?php print $item->title; ?>
      </div>
      <div class="promo-item-chain">
        <?php print 'Available at ' . $item->retailer->name; ?>
      </div>
      <div class="promo-item-restrictions">
        <?php print $item->additional; ?>
      </div>
        <a href="#" rel="<?php print $item->id; ?>" class="css-button small add-to-sl">Add to My Shopping List</a>
    </div>
  </div>
<?php endfor; ?>

