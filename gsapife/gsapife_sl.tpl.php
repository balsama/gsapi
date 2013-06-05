<?php $total_count = $shopping_list->shoppingListResponse->count->itemCount; ?>
<?php $count = count($shopping_list->shoppingListResponse->categories); ?>
<?php $row = 0; ?>
<?php for ($i=0;$i<$count;$i++) : ?>
  <?php $count2 = count($shopping_list->shoppingListResponse->categories[$i]->userMiscellaneousPromotions) ?>
  <?php for ($i2=0;$i2<$count2;$i2++) : ?>
    <?php $zebra = ($row%2 == 0) ? 'odd' : 'even'; ?>
    <?php $item =  $shopping_list->shoppingListResponse->categories[$i]->userMiscellaneousPromotions[$i2]?>
    <?php
    $classes = array(
      'row',
      'row-' . ($row + 1),
      'row-' . $zebra,
      'clearfix',
    );
    if (($row+1) == $total_count) {
      $classes[] = 'last';
    }
    ?>
      <div class="<?php print implode(' ', $classes); ?>">
      <div class="image promo-item-image">
        <?php print theme('image', $item->imageUrl, '', '', array('width' => 50, 'height' => 50), FALSE); ?>
      </div>
      <div class="promo-item-details clearfix">
        <div class="promo-item-title">
          <?php print $item->defaultDisplayDescription; ?>
        </div>
        <div class="promo-item-savings text-color1">
          <?php print $item->title; ?>
        </div>
        <div class="promo-item-chain">
          <?php print 'Available at ' . $item->chains->name; ?>
        </div>
        <div class="promo-item-restrictions">
          <?php print $item->additional; ?>
        </div>
          <a href="#" rel="<?php print $item->id ?>" class="ip-remove" title="remove">Remove</a>
      </div>
    </div>
    <?php
    $row++;
    if ($row == 5) {
      break 2;
    }
    ?>
  <?php endfor; ?>
<?php endfor; ?>
<div class="sl-print-view">
  <?php print l('Print Shopping List', 'gsapi/sl-print', array('html' => TRUE, 'attributes' => array('class' => 'css-button small sl-print-sidebar'))); ?>
  <?php
  $slic = gsapi_gslic();
  if ($slic > 5) {
    print l('See All (' . ($slic - 5) . ' More) &raquo;', 'gsapi/sl-view', array('html' => TRUE, 'attributes' => array('class' => 'sl-view-full-list')));
  }
  ?>
</div>
<iframe id="sl-print-source" class="element-hidden" name="sl-print-source"></iframe>
