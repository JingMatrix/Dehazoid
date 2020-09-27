package org.opencv.samples.tutorial2;

public class DeHaze {


    private int r;
    double t0;
    private double omega;
    private double eps;

    private int width,height;


    public DeHaze(int r, double t0, double omega, double eps, int width, int height){
        this.r = r;
        this.t0 = t0;
        this.omega = omega;
        this.eps = eps;

        this.width = width;
        this.height = height;

        n_createHazeRemoveModel(r, t0, omega, eps, width, height);
    }


    public void videoHazeRemove(long src, long dst){
        n_videoHazeRemove(src, dst);

    }

    private static native void n_createHazeRemoveModel(int r, double t0, double omega,
                                                       double eps, int width, int height);


    private static native void n_videoHazeRemove(long src, long dst);
}
