#pragma once

#include <GL/glew.h>
#include <QGLWidget>
#include <QGLFormat>
#include <QTimer>

#include "../Parametric/ParametricCurves3.h"
#include "../Parametric/ParametricSurfaces3.h"
#include "../Cyclic/CyclicCurve3.h"
#include "../Core/ShaderPrograms.h"
#include "../B-spline/BicubicBSplinePatch.h"
#include "../B-spline/BicubicBSplineArc.h"


namespace cagd
{
    class GLWidget: public QGLWidget
    {
        Q_OBJECT

    private:

        // variables defining the projection matrix
        float       _aspect;            // aspect ratio of the rendering window
        float       _fovy;              // field of view in direction y
        float       _z_near, _z_far;    // distance of near and far clipping planes

        // variables defining the model-view matrix;
        float       _eye[3], _center[3], _up[3];

        // variables needed by transformations;
        int         _angle_x, _angle_y, _angle_z;
        double      _zoom;
        double      _trans_x, _trans_y, _trans_z;

        // your other declarations;
        int         _index, _cc_index, _page_index;
        int         _ps_index, _mo_index, _shader_index;
        int         _patch_index = 0;
        int         _patch_i=1, _patch_j=1,_dcoord_i=1,_dcoord_j=1;
        double      _modify_x=0, _modify_y=0, _modify_z=0;

        // variables needed by parametric curves;
        RowMatrix<ParametricCurve3*> _pc;
        RowMatrix<GenericCurve3*> _image_of_pc;
        GLuint _num_of_pc;

        // variables needed by parametric surfaces;
        RowMatrix<ParametricSurface3*> _ps;
        RowMatrix<TriangulatedMesh3*> _image_of_ps;
        GLuint _num_of_ps;

        // CyclicCurve variables;
        GLuint _n;              // num of cyclic curve points
        RowMatrix<CyclicCurve3*> _cc;
        RowMatrix<GenericCurve3*> _img_cc;
        GLuint _num_of_cc;

        ColumnMatrix<DCoordinate3>  _interp_cc_derivatives;
        ColumnMatrix<GLdouble>      _interp_cc_nodes;

        // varibles needed by models;
        RowMatrix<TriangulatedMesh3*> _image_of_mo;
        GLuint _num_of_mo;

        GLuint _mod;
        GLuint _div;

        // dynamic vertex buffers;
        QTimer* _timer;
        GLfloat _angle;

        // variables needed by shaders
        ShaderProgram _shader;
        GLfloat _scale_factor = 1.0f;
        GLfloat _smoothing = 1.0f;
        GLfloat _shading = 1.0f;

        // B-spline Patch variables
        //BicubicBSplinePatch _patch;
        //BicubicBSplinePatch _patch2;
        GLuint cGridn, cGridm, nPatchn, nPatchm;


        Matrix<BicubicBSplinePatch*> _patch_toroid;
        Matrix<BicubicBSplinePatch*> _patch_cylindric;
        Matrix<BicubicBSplinePatch*> _patch_loaded;
        BicubicBSplinePatch _patch;

        RowMatrix<GenericCurve3*>* _uLines;
        RowMatrix<GenericCurve3*>* _vLines;
        Matrix<RowMatrix<GenericCurve3*>*> _patch_uLines_toroid;
        Matrix<RowMatrix<GenericCurve3*>*> _patch_vLines_toroid;
        Matrix<RowMatrix<GenericCurve3*>*> _patch_uLines_cylindric;
        Matrix<RowMatrix<GenericCurve3*>*> _patch_vLines_cylindric;

        GLuint _uLine_num, _vLine_num;

        Matrix<TriangulatedMesh3*> bi_toroid;
        Matrix<TriangulatedMesh3*> bi_cylindric;
        Matrix<TriangulatedMesh3*> bi_loaded;

        TriangulatedMesh3 *_before_interpolation, *_after_interpolation;

        // B-spline Arc variables
        // GLuint _n;              // num of Arc points points, 4 by default
        RowMatrix<BicubicBSplineArc*> _bspa;
        RowMatrix<GenericCurve3*> _img_bspa;
        GLuint _num_of_bspa;

        ColumnMatrix<GLdouble>      _interp_bspa_nodes;
        ColumnMatrix<DCoordinate3>  _interp_bspa_derivatives;

    public:
        // special and default constructor
        // the format specifies the properties of the rendering window
        GLWidget(QWidget* parent = 0, const QGLFormat& format = QGL::Rgba | QGL::DepthBuffer | QGL::DoubleBuffer);

        // redeclared virtual functions
        void initializeGL();
        void paintGL();
        void resizeGL(int w, int h);

        virtual ~GLWidget();

    public slots:
        // public event handling methods/slots
        void set_angle_x(int value);
        void set_angle_y(int value);
        void set_angle_z(int value);

        void set_zoom_factor(double value);

        void set_trans_x(double value);
        void set_trans_y(double value);
        void set_trans_z(double value);

        void set_parametric_curve_index(int index);
        void set_cyclic_curve_index(int index);
        void set_parametric_surface_index(int index);
        void set_models_index(int index);

        void init_parametric_curves();
        void init_cyclic_curves();
        void init_parametric_surfaces();
        void init_models();
        void init_patch();
        void init_bspline_arc();
        void init_shader(int index);

        void render_pc();
        void render_cc();
        void render_ps();
        void render_mo();
        void render_bspline_arc();
        void render_patch();

        void _animate();
        void start_animate();
        void stop_animate();
        void set_shader_scale_factor(double value);
        void set_shader_smoothing(double value);
        void set_shader_shading(double value);
        void set_shader_index(int index);
        void set_patch_index(int index);
        void modify();
        void set_patch_i(double value);
        void set_patch_j(double value);
        void set_dcoord_i(double value);
        void set_dcoord_j(double value);
        void set_modify_x(double value);
        void set_modify_y(double value);
        void set_modify_z(double value);
        void save_patch( const Matrix<BicubicBSplinePatch*>& _tpatch );
        void load_patch( Matrix<BicubicBSplinePatch*>& _tpatch );
        void callload();
        void callsave();

        DCoordinate3 getCylinderPoint(GLuint i, GLuint j, GLuint n, GLuint m, GLuint r=1, GLfloat a=-1, GLfloat b=1);
        DCoordinate3 getTorusPoint(GLuint i, GLuint j, GLuint n, GLuint m, GLfloat r=0.75, GLfloat R=1.5);
    };
}
