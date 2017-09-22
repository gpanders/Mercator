# Mercator

The goal of Project Mercator is to autonomously build three-dimensional, high
definition maps. This program accepts as input a
[COLMAP](https://colmap.github.io) sparse reconstruction and attempts
to find the optimal position for a new image (or camera) that, when taken,
would most improve the "quality" of the reconstruction.

The "quality" of a reconstruction is defined by the following criterion that
each 3D point in the reconstruction must meet:
 - **Uncertainty**. Each point in the 3D reconstruction has an uncertainty
   covariance matrix associated with it. This matrix represents how "unsure"
   the exact location of that point is. We evaluate the maximum eigenvalue of
   this matrix for each point and check that it falls below a given threshold.
 - **Number of cameras**. Each point is "seen" by a number of images in the
   reconstruction (note that here we use the words "camera" and "image"
   interchangably). If a point is visible in more images, we have more
   confidence that that point is really where it ought to be. However, if a
   point is seen by fewer cameras, we have less confidence.
 - **Resolution analysis**. The ground sampling distance (GSD) of a camera is
   defined as the number of square meters one pixel in the image covers. A
   smaller GSD is equivalent to a higher spatial resolution. Higher spatial
   resolution means an image is able to see more details and texture
   surrounding each point, but it loses valuable information about feature
   correspondences in the overall scene. If the images that "see" each point
   have poor GSD, then that point is a candidate for improvement. Further, the
   user can supply a minimum GSD that factors into the optimal position of the
   new camera.
 - **Stereo configuration analysis**. The depth information of a scene is
   inferred by the stereo configuration of two or more cameras. A greater angle
   between two cameras results in a better depth estimate, but reduces feature
   correspondences. Like with resolution, there is a sweet spot that an image
   tries to meet. If the images corresponding to a point fail this test, that
   point is marked as a candidate for improvement.

Much of the code in this project is inspired by the great work that Johannes
Schönberger has done with [COLMAP](https://github.com/colmap/colmap).
   
This project is written and maintained by the [University of Texas
Radionavigation Lab](https://rnl.ae.utexas.edu) and is licensed under the [MIT
License](https://github.com/radionavlab/mercator/blob/master/LICENSE).
