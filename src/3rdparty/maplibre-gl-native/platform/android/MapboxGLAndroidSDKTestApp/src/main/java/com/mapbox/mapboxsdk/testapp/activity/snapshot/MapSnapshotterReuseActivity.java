package com.mapbox.mapboxsdk.testapp.activity.snapshot;

import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;

import androidx.appcompat.app.AppCompatActivity;

import com.mapbox.mapboxsdk.camera.CameraPosition;
import com.mapbox.mapboxsdk.geometry.LatLng;
import com.mapbox.mapboxsdk.geometry.LatLngBounds;
import com.mapbox.mapboxsdk.maps.Style;
import com.mapbox.mapboxsdk.snapshotter.MapSnapshot;
import com.mapbox.mapboxsdk.snapshotter.MapSnapshotter;
import com.mapbox.mapboxsdk.testapp.R;

import java.util.Random;

/**
 * Test activity showing how to use a the {@link MapSnapshotter}
 */
public class MapSnapshotterReuseActivity extends AppCompatActivity implements MapSnapshotter.SnapshotReadyCallback {

  private MapSnapshotter mapSnapshotter;
  private View fab;

  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.activity_map_snapshotter_reuse);

    fab = findViewById(R.id.fab);
    fab.setVisibility(View.INVISIBLE);
    fab.setOnClickListener(v -> {
      fab.setVisibility(View.INVISIBLE);

      mapSnapshotter.setStyleUrl(getRandomStyle());
      if (random.nextInt(2) == 0) {
        mapSnapshotter.setCameraPosition(getRandomCameraPosition());
      } else {
        mapSnapshotter.setRegion(getRandomBounds());
      }
      if (random.nextInt(2) == 0) {
        mapSnapshotter.setSize(512, 512);
      } else {
        mapSnapshotter.setSize(256, 256);
      }
      mapSnapshotter.start(MapSnapshotterReuseActivity.this);
    });

    mapSnapshotter = new MapSnapshotter(
      getApplicationContext(),
      new MapSnapshotter.Options(512, 512).withStyleBuilder(new Style.Builder().fromUri(getRandomStyle()))
    );

    mapSnapshotter.start(MapSnapshotterReuseActivity.this);
  }

  @Override
  public void onSnapshotReady(MapSnapshot snapshot) {
    fab.setVisibility(View.VISIBLE);
    ImageView imageView = findViewById(R.id.snapshot_image);
    imageView.setImageBitmap(snapshot.getBitmap());
  }

  private LatLngBounds getRandomBounds() {
    return new LatLngBounds.Builder()
      .include(new LatLng(randomInRange(5, 10), randomInRange(-5, 5)))
      .include(new LatLng(randomInRange(-5, 5), randomInRange(5, 10)))
      .build();
  }

  private CameraPosition getRandomCameraPosition() {
    return new CameraPosition.Builder()
      .target(new LatLng(randomInRange(-80, 80), randomInRange(-160, 160)))
      .zoom(randomInRange(2, 10))
      .bearing(randomInRange(0, 90))
      .build();
  }

  public String getRandomStyle() {
    switch (random.nextInt(5)) {
      case 0:
        return Style.getPredefinedStyle("Pastel");
      case 1:
        return Style.getPredefinedStyle("Bright");
      case 2:
        return Style.getPredefinedStyle("Streets");
      case 3:
        return Style.getPredefinedStyle("Outdoor");
      case 4:
        return Style.getPredefinedStyle("Satellite Hybrid");
      default:
        return Style.getPredefinedStyle("Streets");
    }
  }

  private static Random random = new Random();

  public static float randomInRange(float min, float max) {
    return (random.nextFloat() * (max - min)) + min;
  }

}
