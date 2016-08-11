/*==============================================================================

  Program: 3D Slicer

  Copyright (c) Laboratory for Percutaneous Surgery (PerkLab)
  Queen's University, Kingston, ON, Canada. All Rights Reserved.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  This file was originally developed by Csaba Pinter, PerkLab, Queen's University
  and was supported through the Applied Cancer Research Unit program of Cancer Care
  Ontario with funds provided by the Ontario Ministry of Health and Long-Term Care

==============================================================================*/

#ifndef __qMRMLBeamParametersTabWidget_h
#define __qMRMLBeamParametersTabWidget_h

// Beams includes
#include "qSlicerBeamsModuleWidgetsExport.h"

// Qt includes
#include <QTabWidget>

// CTK includes
#include <ctkPimpl.h>
#include <ctkVTKObject.h>

class vtkMRMLNode;
class qMRMLBeamParametersTabWidgetPrivate;
class QCheckBox;

/// \ingroup SlicerRt_QtModules_Beams_Widgets
class Q_SLICER_MODULE_BEAMS_WIDGETS_EXPORT qMRMLBeamParametersTabWidget : public QTabWidget
{
  Q_OBJECT
  QVTK_OBJECT

public:
  /// Name of property in widgets specifying which attribute it belongs to in the beam parameter nodes
  static const char* BEAM_PARAMETER_NODE_ATTRIBUTE_PROPERTY;
  /// Name of property in checkbox widgets specifying the beam parameter widgets to be enabled/disabled
  /// based on the checked state of the checkbox by containing their parameter node attribute names (see above)
  static const char* DEPENDENT_PARAMETER_NAMES_PROPERTY;
  /// Name of property in widgets indicating whether the parameter it represents is used by the current engine
  static const char* USED_BY_CURRENT_ENGINE_PROPERTY;

public:
  typedef QTabWidget Superclass;
  /// Constructor
  explicit qMRMLBeamParametersTabWidget(QWidget* parent = 0);
  /// Destructor
  virtual ~qMRMLBeamParametersTabWidget();

  /// Get RT beam MRML node
  Q_INVOKABLE vtkMRMLNode* beamNode();

  /// Get widget of tab widget by name.
  /// If no tab of the specified name exists, a new one is created with that name
  /// \param tabName Name of the tab to return
  /// \return Tab widget with given name
  QWidget* beamParametersTab(QString tabName);

  /// Add floating point parameter to the given tab of the beam parameters widget
  /// \param TODO
  /// \param slider If true then a slider is created, otherwise (by default) a spin box with text edit
  void addBeamParameterFloatingPointNumber(
    QString tabName, QString parameterName, QString parameterLabel,
    QString tooltip, double minimumValue, double maximumValue,
    double defaultValue, double stepSize, int precision, bool slider=false );

  /// Add new multiple choice beam parameter to beam parameters widget as a combo box
  /// \param TODO
  void addBeamParameterComboBox(
    QString tabName, QString parameterName, QString parameterLabel,
    QString tooltip, QStringList options, int defaultIndex );

  /// Add new boolean type beam parameter to beam parameters widget as a check box
  /// \param TODO
  /// \param dependentParameterNames Names of parameters (full names including engine prefix) that
  ///   need to be enabled/disabled based on the checked state of the created checkbox
  void addBeamParameterCheckBox(
    QString tabName, QString parameterName, QString parameterLabel,
    QString tooltip, bool defaultValue, QStringList dependentParameterNames=QStringList() );

  /// Show/hide beam parameter with specified name.
  /// Removes tab if becomes empty after hiding parameter, and re-adds tab if needed after showing parameter
  bool setBeamParameterVisible(QString parameterName, bool visible);

  /// Hide tabs where all parameters are hidden, and show tabs that contain visible parameters
  void updateTabVisibility();

public slots:
  /// Set RT beam MRML node
  void setBeamNode(vtkMRMLNode* node);

  /// Handle floating point parameter changes in engine-specific beam parameter widgets
  void doubleBeamParameterChanged(double);

  /// Handle integer parameter changes in engine-specific beam parameter widgets
  void integerBeamParameterChanged(int);

  /// Handle boolean parameter changes in engine-specific beam parameter widgets
  /// (converts the input integer to boolean)
  void booleanBeamParameterChanged(int);

signals:

protected slots:
  /// Update from beam node state
  void updateWidgetFromMRML();

  /// Enable/disable widgets for dependent parameters for a checkbox based on the checkbox's state
  void updateDependentParameterWidgetsForCheckbox(QCheckBox* checkBox);

// Default beam parameter handler functions
protected slots:
  // Geometry page
  void mlcPositionDoubleArrayNodeChanged(vtkMRMLNode* node);
  void sourceDistanceChanged(double);
  void xJawsPositionValuesChanged(double, double);
  void yJawsPositionValuesChanged(double, double);
  void collimatorAngleChanged(double);
  void gantryAngleChanged(double);
  void couchAngleChanged(double);

  // Visualization page
  void updateDRRClicked();
  void beamEyesViewClicked(bool);
  void contoursInBEWClicked(bool);

protected:
  QScopedPointer<qMRMLBeamParametersTabWidgetPrivate> d_ptr;

private:
  Q_DECLARE_PRIVATE(qMRMLBeamParametersTabWidget);
  Q_DISABLE_COPY(qMRMLBeamParametersTabWidget);
};

#endif 