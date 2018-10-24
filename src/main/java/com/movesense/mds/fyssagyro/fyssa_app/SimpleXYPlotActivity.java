package com.movesense.mds.fyssagyro.fyssa_app;

import android.app.Activity;
import android.graphics.*;
import android.os.Bundle;
import android.util.Log;

import com.androidplot.util.PixelUtils;
import com.androidplot.xy.SimpleXYSeries;
import com.androidplot.xy.XYSeries;
import com.androidplot.xy.*;
import com.movesense.mds.fyssagyro.R;

import java.text.FieldPosition;
import java.text.Format;
import java.text.ParsePosition;
import java.util.*;

/**
 * A simple XYPlot
 */
public class SimpleXYPlotActivity extends Activity {

    private String TAG = this.getClass().getSimpleName();
    private XYPlot plot;
    FyssaApp app;
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.simple_xy_plot_example);

        // initialize our XYPlot reference:
        plot = (XYPlot) findViewById(R.id.plot);
        app = (FyssaApp) getApplication();


        ArrayList<Float> x = new ArrayList<>();
        ArrayList<Float> y = new ArrayList<>();
        for (int i = 0; i < app.plottable.size()/2; i++) {
            x.add(app.plottable.get(i*2)*10);
            y.add(app.plottable.get(i*2+1)*10);
        }
        String s = "Found processed data!";
        for (int i = 0; i < x.size(); i++) s = s + "(" + x.get(i) + ", " + y.get(i) + ") ";
        Log.d(TAG, s);
        // turn the above arrays into XYSeries':
        // (Y_VALS_ONLY means use the element index as the x value)
        XYSeries series1 = new SimpleXYSeries(x,y, "Traj1");

        // create formatters to use for drawing a series using LineAndPointRenderer
        // and configure them from xml:
        LineAndPointFormatter series1Format =new LineAndPointFormatter(Color.RED, Color.GREEN, null, null);

        LineAndPointFormatter series2Format =new LineAndPointFormatter(Color.RED, Color.GREEN, null, null);

        // add an "dash" effect to the series2 line:
        series2Format.getLinePaint().setPathEffect(new DashPathEffect(new float[] {

                // always use DP when specifying pixel sizes, to keep things consistent across devices:
                PixelUtils.dpToPix(20),
                PixelUtils.dpToPix(15)}, 0));

        // just for fun, add some smoothing to the lines:
        // see: http://androidplot.com/smooth-curves-and-androidplot/
        series1Format.setInterpolationParams(
                new CatmullRomInterpolator.Params(10, CatmullRomInterpolator.Type.Centripetal));

        // add a new series' to the xyplot:
        plot.addSeries(series1, series1Format);
/*
        plot.getGraph().getLineLabelStyle(XYGraphWidget.Edge.BOTTOM).setFormat(new Format() {
            @Override
            public StringBuffer format(Object obj, StringBuffer toAppendTo, FieldPosition pos) {
                int i = Math.round(((Number) obj).floatValue());
                return toAppendTo.append(domainLabels[i]);
            }
            @Override
            public Object parseObject(String source, ParsePosition pos) {
                return null;
            }
        });*/
    }
}
