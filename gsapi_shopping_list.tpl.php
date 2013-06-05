<h3 class="title block-title lucida">My Shopping List<span></span>
  <?php print theme('image', drupal_get_path('module', 'gsapi') . '/includes/images/gs-logo.png', '', '', array('class' => 'sl-print-gs-logo')); ?>
</h3>
<div class="shopping-list">
  <hr />
  <div class="sl-print-view">
    <?php print l('Print Shopping List', 'gsapi/sl-print', array('html' => TRUE, 'attributes' => array('class' => 'css-button small sl-print'))); ?>
    <?php print l('Remove All From Shopping List', 'gsapi/sl-view', array('html' => TRUE, 'attributes' => array('class' => 'sl-remove-all'), 'query' => array('reset' => TRUE))); ?>
  </div>
  <hr />
  <?php $total_count = $shopping_list->shoppingListResponse->count->itemCount; ?>
  <?php $count = count($shopping_list->shoppingListResponse->categories); ?>
  <?php $row = 0; ?>
  <div class="rows">
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
          <?php print theme('image', $item->imageUrl, '', '', array('width' => 100, 'height' => 100), FALSE); ?>
        </div>
        <div class="promo-item-details">
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
      <?php $row++;?>
    <?php endfor; ?>
  <?php endfor; ?>
  </div>
  <hr />
  <div class="sl-print-view">
    <?php print l('Print Shopping List', 'gsapi/sl-print', array('html' => TRUE, 'attributes' => array('class' => 'css-button small sl-print'))); ?>
    <?php print l('Remove All From Shopping List', 'gsapi/sl-view', array('html' => TRUE, 'attributes' => array('class' => 'sl-remove-all'), 'query' => array('reset' => TRUE))); ?>
  </div>
  <hr />
</div>
