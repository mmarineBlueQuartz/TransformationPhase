/* ============================================================================
 * Copyright (c) 2011 Michael A. Jackson (BlueQuartz Software)
 * Copyright (c) 2011 Dr. Michael A. Groeber (US Air Force Research Laboratories)
 * Copyright (c) 2014 Dr. Joseph C. Tucker (UES, Inc.)
 * Copyright (c) 2014 Sudipto Mandal & Prof. Anthony D. Rollett (Carnegie Mellon 
 * University)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this
 * list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 *
 * Neither the name of Joseph C. Tucker, Michael A. Groeber, Michael A. Jackson,
 * Sudipto Mandal, Anthony D. Rollett, UES, Inc., the US Air Force, BlueQuartz  
 * Software nor the names of its may be used to endorse or promote products derived 
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  This code was written under United States Air Force Contract number
 *     FA8650-07-D-5800 and FA8650-10-D-5226 and The Boeing Company
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#ifndef INSERTTRANSFORMATIONPHASES_H_
#define INSERTTRANSFORMATIONPHASES_H_

#include <vector>
#include <QtCore/QString>

#include <boost/shared_array.hpp>

#include "DREAM3DLib/DREAM3DLib.h"
#include "DREAM3DLib/Common/DREAM3DSetGetMacros.h"
#include "DREAM3DLib/DataArrays/IDataArray.h"

#include "DREAM3DLib/Common/AbstractFilter.h"
#include "DREAM3DLib/DataContainers/VolumeDataContainer.h"
#include "DREAM3DLib/OrientationOps/OrientationOps.h"
#include "DREAM3DLib/DataArrays/NeighborList.hpp"
#include "Plugins/SyntheticBuilding/SyntheticBuildingConstants.h"

/**
 * @class InsertTransformationPhases InsertTransformationPhases.h DREAM3DLib/SyntheticBuildingFilters/InsertTransformationPhases.h
 * @brief
 * @author Joseph C. Tucker (UES, Inc.)
 * @author Sudipto Mandal (CMU)
 * @date July 29, 2014
 * @version 5.1
 */
class InsertTransformationPhases : public AbstractFilter
{
    Q_OBJECT /* Need this for Qt's signals and slots mechanism to work */
  public:
    DREAM3D_SHARED_POINTERS(InsertTransformationPhases)
    DREAM3D_STATIC_NEW_MACRO(InsertTransformationPhases)
    DREAM3D_TYPE_MACRO_SUPER(InsertTransformationPhases, AbstractFilter)

    virtual ~InsertTransformationPhases();

    DREAM3D_FILTER_PARAMETER(int, TransCrystalStruct)
    Q_PROPERTY(int TransCrystalStruct READ getTransCrystalStruct WRITE setTransCrystalStruct)
	DREAM3D_FILTER_PARAMETER(float, TransformationPhaseMisorientation)
    Q_PROPERTY(float TransformationPhaseMisorientation READ getTransformationPhaseMisorientation WRITE setTransformationPhaseMisorientation)
    DREAM3D_FILTER_PARAMETER(FloatVec3_t, TransformationPhaseHabitPlane)
    DREAM3D_FILTER_PARAMETER(bool, DefineHabitPlane)
    Q_PROPERTY(bool DefineHabitPlane READ getDefineHabitPlane WRITE setDefineHabitPlane)
	Q_PROPERTY(FloatVec3_t TransformationPhaseHabitPlane READ getTransformationPhaseHabitPlane WRITE setTransformationPhaseHabitPlane)
    DREAM3D_FILTER_PARAMETER(bool, UseAllVariants)
    Q_PROPERTY(bool UseAllVariants READ getUseAllVariants WRITE setUseAllVariants)
    DREAM3D_FILTER_PARAMETER(float, CoherentFrac)
    Q_PROPERTY(float CoherentFrac READ getCoherentFrac WRITE setCoherentFrac)
	DREAM3D_FILTER_PARAMETER(float, TransformationPhaseThickness)
    Q_PROPERTY(float TransformationPhaseThickness READ getTransformationPhaseThickness WRITE setTransformationPhaseThickness)
    DREAM3D_FILTER_PARAMETER(int, NumTransformationPhasesPerFeature)
    Q_PROPERTY(int NumTransformationPhasesPerFeature READ getNumTransformationPhasesPerFeature WRITE setNumTransformationPhasesPerFeature)
    DREAM3D_FILTER_PARAMETER(float, PeninsulaFrac)
    Q_PROPERTY(float PeninsulaFrac READ getPeninsulaFrac WRITE setPeninsulaFrac)

	DREAM3D_FILTER_PARAMETER(DataArrayPath, StatsGenCellEnsembleAttributeMatrixPath)
    Q_PROPERTY(DataArrayPath StatsGenCellEnsembleAttributeMatrixPath READ getStatsGenCellEnsembleAttributeMatrixPath WRITE setStatsGenCellEnsembleAttributeMatrixPath)

	DREAM3D_FILTER_PARAMETER(DataArrayPath, VolCellEnsembleAttributeMatrixPath)
    Q_PROPERTY(DataArrayPath VolCellEnsembleAttributeMatrixPath READ getVolCellEnsembleAttributeMatrixPath WRITE setVolCellEnsembleAttributeMatrixPath)

    DREAM3D_FILTER_PARAMETER(DataArrayPath, CellFeatureAttributeMatrixName)
    Q_PROPERTY(DataArrayPath CellFeatureAttributeMatrixName READ getCellFeatureAttributeMatrixName WRITE setCellFeatureAttributeMatrixName)

	DREAM3D_FILTER_PARAMETER(DataArrayPath, FeatureIdsArrayPath)
    Q_PROPERTY(DataArrayPath FeatureIdsArrayPath READ getFeatureIdsArrayPath WRITE setFeatureIdsArrayPath)
    
	DREAM3D_FILTER_PARAMETER(DataArrayPath, CellEulerAnglesArrayPath)
    Q_PROPERTY(DataArrayPath CellEulerAnglesArrayPath READ getCellEulerAnglesArrayPath WRITE setCellEulerAnglesArrayPath)

    DREAM3D_FILTER_PARAMETER(DataArrayPath, AvgQuatsArrayPath)
    Q_PROPERTY(DataArrayPath AvgQuatsArrayPath READ getAvgQuatsArrayPath WRITE setAvgQuatsArrayPath)

    DREAM3D_FILTER_PARAMETER(DataArrayPath, CentroidsArrayPath)
    Q_PROPERTY(DataArrayPath CentroidsArrayPath READ getCentroidsArrayPath WRITE setCentroidsArrayPath)

    DREAM3D_FILTER_PARAMETER(DataArrayPath, EquivalentDiametersArrayPath)
    Q_PROPERTY(DataArrayPath EquivalentDiametersArrayPath READ getEquivalentDiametersArrayPath WRITE setEquivalentDiametersArrayPath)

    DREAM3D_FILTER_PARAMETER(DataArrayPath, FeatureEulerAnglesArrayPath)
    Q_PROPERTY(DataArrayPath FeatureEulerAnglesArrayPath READ getFeatureEulerAnglesArrayPath WRITE setFeatureEulerAnglesArrayPath)

    DREAM3D_FILTER_PARAMETER(DataArrayPath, FeaturePhasesArrayPath)
    Q_PROPERTY(DataArrayPath FeaturePhasesArrayPath READ getFeaturePhasesArrayPath WRITE setFeaturePhasesArrayPath)

    DREAM3D_FILTER_PARAMETER(QString, FeatureParentIdsArrayName)
    Q_PROPERTY(QString FeatureParentIdsArrayName READ getFeatureParentIdsArrayName WRITE setFeatureParentIdsArrayName)
	
    DREAM3D_FILTER_PARAMETER(QString, NumFeaturesPerParentArrayName)
    Q_PROPERTY(QString NumFeaturesPerParentArrayName READ getNumFeaturesPerParentArrayName WRITE setNumFeaturesPerParentArrayName)
	
	DREAM3D_FILTER_PARAMETER(DataArrayPath, CrystalStructuresArrayPath)
    Q_PROPERTY(DataArrayPath CrystalStructuresArrayPath READ getCrystalStructuresArrayPath WRITE setCrystalStructuresArrayPath)

    DREAM3D_FILTER_PARAMETER(DataArrayPath, PhaseTypesArrayPath)
    Q_PROPERTY(DataArrayPath PhaseTypesArrayPath READ getPhaseTypesArrayPath WRITE setPhaseTypesArrayPath)

    DREAM3D_FILTER_PARAMETER(DataArrayPath, ShapeTypesArrayPath)
    Q_PROPERTY(DataArrayPath ShapeTypesArrayPath READ getShapeTypesArrayPath WRITE setShapeTypesArrayPath)

    DREAM3D_FILTER_PARAMETER(DataArrayPath, NumFeaturesArrayPath)
    Q_PROPERTY(DataArrayPath NumFeaturesArrayPath READ getNumFeaturesArrayPath WRITE setNumFeaturesArrayPath)
	
	virtual const QString getCompiledLibraryName() { return SyntheticBuilding::SyntheticBuildingBaseName; }
	virtual const QString getGroupName() { return DREAM3D::FilterGroups::SyntheticBuildingFilters; }
	virtual const QString getSubGroupName() { return DREAM3D::FilterSubGroups::PackingFilters; }
    virtual const QString getHumanLabel() { return "Insert Tranformation Phases"; }
    virtual const QString getBrandingString() { return SyntheticBuilding::SyntheticBuildingPluginDisplayName + " Filter"; }

    virtual void setupFilterParameters();
    /**
    * @brief This method will write the options to a file
    * @param writer The writer that is used to write the options to a file
    */
    virtual int writeFilterParameters(AbstractFilterParametersWriter* writer, int index);  
    /**
    * @brief This method will read the options from a file
    * @param reader The reader that is used to read the options from a file
    */
    virtual void readFilterParameters(AbstractFilterParametersReader* reader, int index);
    /**
    * @brief Reimplemented from @see AbstractFilter class
    */
    virtual void execute();
    virtual AbstractFilter::Pointer newFilterInstance(bool copyFilterParameters);
    virtual void preflight();

signals:
    void updateFilterParameters(AbstractFilter* filter);
    void parametersChanged();
    void preflightAboutToExecute();
    void preflightExecuted();

  protected:
    InsertTransformationPhases();

	void insert_transformationphases();
	bool place_transformationphase(size_t curFeature, float sample111[], size_t totalFeatures, float plateThickness, float d, size_t numFeatures);
    void peninsula_transformationphase(size_t curFeature, size_t totalFeatures);
	size_t transfer_attributes(size_t totalFeatures, QuatF q, float e[], size_t curFeature);
	void filter_calls();

  private:
    QVector<OrientationOps::Pointer> m_OrientationOps;

    // Cell Data - make sure these are all initialized to NULL in the constructor
    DEFINE_CREATED_DATAARRAY_VARIABLE(int32_t, FeatureIds)
	DEFINE_REQUIRED_DATAARRAY_VARIABLE(float, CellEulerAngles)

    // Feature Data - make sure these are all initialized to NULL in the constructor
	DEFINE_REQUIRED_DATAARRAY_VARIABLE(float, AvgQuats)
	DEFINE_CREATED_DATAARRAY_VARIABLE(bool, Active)
    DEFINE_REQUIRED_DATAARRAY_VARIABLE(float, Centroids)
    DEFINE_REQUIRED_DATAARRAY_VARIABLE(float, EquivalentDiameters)
    DEFINE_REQUIRED_DATAARRAY_VARIABLE(float, FeatureEulerAngles)
    DEFINE_REQUIRED_DATAARRAY_VARIABLE(int32_t, FeaturePhases)
    DEFINE_CREATED_DATAARRAY_VARIABLE(int32_t, FeatureParentIds)
	DEFINE_CREATED_DATAARRAY_VARIABLE(int32_t, NumFeaturesPerParent)

    // Ensemble Data - make sure these are all initialized to NULL in the constructor
    DEFINE_REQUIRED_DATAARRAY_VARIABLE(uint32_t, CrystalStructures)
    DEFINE_REQUIRED_DATAARRAY_VARIABLE(uint32_t, PhaseTypes)
    DEFINE_REQUIRED_DATAARRAY_VARIABLE(uint32_t, ShapeTypes)
    DEFINE_REQUIRED_DATAARRAY_VARIABLE(int32_t, NumFeatures)

    // All other private variables
    void dataCheck();
    void updateFeatureInstancePointers();
    void updateStatsGenEnsembleInstancePointers();
    void updateVolEnsembleInstancePointers();

    InsertTransformationPhases(const InsertTransformationPhases&); // Copy Constructor Not Implemented
    void operator=(const InsertTransformationPhases&); // Operator '=' Not Implemented
};

#endif /* INSERTTRANSFORMATIONPHASES_H_ */