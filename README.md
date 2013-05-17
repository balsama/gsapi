gsapi
=====

Drupal wrapper for the Grocery Server API. This implementation requires that
you provide Grocery Server with your recipes and that they have been imported
into the Grocery Service API.

Functions
---------

* **Get Recipe Details**

    gsapi_grd($rid)

  Parameters: $rid integer  
    Recipe ID as defined in the XML document provided to Grocery Server.
    Usually the Drupal Node ID.

  Return: array  
    Array representing the recipe and any current promotions for ingredients
    based on the user's zip code. Results are cached for 24 hours.

* **Get Promotion Count**

    gsapi_gpc($rid)

  Parameters: $rid integer  
    Recipe ID as defined in the XML document provided to Grocery Server.
    Usually the Drupal Node ID.

  Return: integer
    The number of current promotions for the provided Recipe ID.

