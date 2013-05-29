<?php //dpm($shopping_list); ?>

<?php $count = count($shopping_list->shoppingListResponse->categories); ?>
<?php for ($i=0;$i<$count;$i++) : ?>
  <?php $zebra = ($i%2) ? 'even' : 'odd'; ?>
  <?php $item =  $shopping_list->shoppingListResponse->categories[$i]->userMiscellaneousPromotions[0]?>
  <?php dpm($item); ?>
  <div class="row row-<?php print $i+1; ?> row-<?php print $zebra; ?> clearfix">
    <div class="image promo-item-image">
      <?php print theme('image', $item->imageUrl, '', '', array('width' => 50, 'height' => 50), FALSE); ?>
    </div>
    <div class="promo-item-details clearfix">
      <div class="promo-item-title">
        <?php print $item->defaultDisplayDescription; ?>
      </div>
      <div class="promo-item-savings">
        <?php print 'Only $' . $item->retailUnitSalePrice; ?>
      </div>
      <div class="promo-item-chain">
        <?php print 'Available at ' . $item->chains->name; ?>
      </div>
      <div class="promo-item-restrictions">
        <?php print $item->chains->name; ?>
      </div>
    </div>
  </div>
<?php endfor; ?>
