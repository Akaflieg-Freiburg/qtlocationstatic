package com.mapbox.mapboxsdk.testapp.activity.style;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.os.Handler;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import com.mapbox.mapboxsdk.Mapbox;
import com.mapbox.mapboxsdk.geometry.LatLng;
import com.mapbox.mapboxsdk.geometry.LatLngQuad;
import com.mapbox.mapboxsdk.maps.MapView;
import com.mapbox.mapboxsdk.maps.MapboxMap;
import com.mapbox.mapboxsdk.maps.OnMapReadyCallback;
import com.mapbox.mapboxsdk.maps.Style;
import com.mapbox.mapboxsdk.style.layers.RasterLayer;
import com.mapbox.mapboxsdk.style.sources.ImageSource;
import com.mapbox.mapboxsdk.testapp.R;
import com.mapbox.mapboxsdk.utils.BitmapUtils;

/**
 * Test activity showing how to use a series of images to create an animation
 * with an ImageSource
 * <p>
 * GL-native equivalent of https://maplibre.org/maplibre-gl-js-docs/example/animate-images/
 * </p>
 */
public class AnimatedImageSourceActivity extends AppCompatActivity implements OnMapReadyCallback {

  private static final String ID_IMAGE_SOURCE = "animated_image_source";
  private static final String ID_IMAGE_LAYER = "animated_image_layer";

  private MapView mapView;
  private final Handler handler = new Handler();
  private Runnable runnable;

  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.activity_animated_image_source);
    mapView = findViewById(R.id.mapView);
    mapView.onCreate(savedInstanceState);
    mapView.getMapAsync(this);
  }

  @Override
  public void onMapReady(@NonNull final MapboxMap map) {
    LatLngQuad quad = new LatLngQuad(
      new LatLng(46.437, -80.425),
      new LatLng(46.437, -71.516),
      new LatLng(37.936, -71.516),
      new LatLng(37.936, -80.425));

    final ImageSource imageSource = new ImageSource(ID_IMAGE_SOURCE, quad, R.drawable.southeast_radar_0);
    final RasterLayer layer = new RasterLayer(ID_IMAGE_LAYER, ID_IMAGE_SOURCE);
    map.setStyle(new Style.Builder()
        .fromUri(Style.getPredefinedStyle("Streets"))
        .withSource(imageSource)
        .withLayer(layer), style -> {
        runnable = new RefreshImageRunnable(imageSource, handler);
        handler.postDelayed(runnable, 100);
      }
    );
  }

  @Override
  protected void onStart() {
    super.onStart();
    mapView.onStart();
  }

  @Override
  public void onResume() {
    super.onResume();
    mapView.onResume();
  }

  @Override
  public void onPause() {
    super.onPause();
    mapView.onPause();
  }

  @Override
  protected void onStop() {
    super.onStop();
    mapView.onStop();
    handler.removeCallbacks(runnable);
  }

  @Override
  protected void onDestroy() {
    super.onDestroy();
    mapView.onDestroy();
  }

  @Override
  protected void onSaveInstanceState(Bundle outState) {
    super.onSaveInstanceState(outState);
    mapView.onSaveInstanceState(outState);
  }

  private static class RefreshImageRunnable implements Runnable {

    private ImageSource imageSource;
    private Handler handler;
    private Bitmap[] drawables;
    private int drawableIndex;

    Bitmap getBitmap(int resourceId) {
      Context context = Mapbox.getApplicationContext();
      Drawable drawable = BitmapUtils.getDrawableFromRes(context, resourceId);
      if (drawable instanceof BitmapDrawable) {
        BitmapDrawable bitmapDrawable = (BitmapDrawable) drawable;
        return bitmapDrawable.getBitmap();
      }
      return null;
    }

    RefreshImageRunnable(ImageSource imageSource, Handler handler) {
      this.imageSource = imageSource;
      this.handler = handler;
      drawables = new Bitmap[4];
      drawables[0] = getBitmap(R.drawable.southeast_radar_0);
      drawables[1] = getBitmap(R.drawable.southeast_radar_1);
      drawables[2] = getBitmap(R.drawable.southeast_radar_2);
      drawables[3] = getBitmap(R.drawable.southeast_radar_3);
      drawableIndex = 1;
    }

    @Override
    public void run() {
      imageSource.setImage(drawables[drawableIndex++]);
      if (drawableIndex > 3) {
        drawableIndex = 0;
      }
      handler.postDelayed(this, 1000);
    }
  }
}
