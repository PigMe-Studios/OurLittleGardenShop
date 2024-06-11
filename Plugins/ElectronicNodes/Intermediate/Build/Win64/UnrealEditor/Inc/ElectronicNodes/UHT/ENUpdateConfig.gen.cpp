// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ElectronicNodes/Private/Popup/ENUpdateConfig.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeENUpdateConfig() {}
// Cross Module References
	DEVELOPERSETTINGS_API UClass* Z_Construct_UClass_UDeveloperSettings();
	ELECTRONICNODES_API UClass* Z_Construct_UClass_UENUpdateConfig();
	ELECTRONICNODES_API UClass* Z_Construct_UClass_UENUpdateConfig_NoRegister();
	UPackage* Z_Construct_UPackage__Script_ElectronicNodes();
// End Cross Module References
	void UENUpdateConfig::StaticRegisterNativesUENUpdateConfig()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UENUpdateConfig);
	UClass* Z_Construct_UClass_UENUpdateConfig_NoRegister()
	{
		return UENUpdateConfig::StaticClass();
	}
	struct Z_Construct_UClass_UENUpdateConfig_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PluginVersionUpdate_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_PluginVersionUpdate;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UENUpdateConfig_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UDeveloperSettings,
		(UObject* (*)())Z_Construct_UPackage__Script_ElectronicNodes,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UENUpdateConfig_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UENUpdateConfig_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "Popup/ENUpdateConfig.h" },
		{ "ModuleRelativePath", "Private/Popup/ENUpdateConfig.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UENUpdateConfig_Statics::NewProp_PluginVersionUpdate_MetaData[] = {
		{ "ModuleRelativePath", "Private/Popup/ENUpdateConfig.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UENUpdateConfig_Statics::NewProp_PluginVersionUpdate = { "PluginVersionUpdate", nullptr, (EPropertyFlags)0x0010000000004000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UENUpdateConfig, PluginVersionUpdate), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UENUpdateConfig_Statics::NewProp_PluginVersionUpdate_MetaData), Z_Construct_UClass_UENUpdateConfig_Statics::NewProp_PluginVersionUpdate_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UENUpdateConfig_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UENUpdateConfig_Statics::NewProp_PluginVersionUpdate,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UENUpdateConfig_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UENUpdateConfig>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UENUpdateConfig_Statics::ClassParams = {
		&UENUpdateConfig::StaticClass,
		"EditorPerProjectUserSettings",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UENUpdateConfig_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UENUpdateConfig_Statics::PropPointers),
		0,
		0x001000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UENUpdateConfig_Statics::Class_MetaDataParams), Z_Construct_UClass_UENUpdateConfig_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UENUpdateConfig_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_UENUpdateConfig()
	{
		if (!Z_Registration_Info_UClass_UENUpdateConfig.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UENUpdateConfig.OuterSingleton, Z_Construct_UClass_UENUpdateConfig_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UENUpdateConfig.OuterSingleton;
	}
	template<> ELECTRONICNODES_API UClass* StaticClass<UENUpdateConfig>()
	{
		return UENUpdateConfig::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UENUpdateConfig);
	UENUpdateConfig::~UENUpdateConfig() {}
	struct Z_CompiledInDeferFile_FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_ElectronicNodes_Source_ElectronicNodes_Private_Popup_ENUpdateConfig_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_ElectronicNodes_Source_ElectronicNodes_Private_Popup_ENUpdateConfig_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UENUpdateConfig, UENUpdateConfig::StaticClass, TEXT("UENUpdateConfig"), &Z_Registration_Info_UClass_UENUpdateConfig, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UENUpdateConfig), 2068726952U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_ElectronicNodes_Source_ElectronicNodes_Private_Popup_ENUpdateConfig_h_2469451831(TEXT("/Script/ElectronicNodes"),
		Z_CompiledInDeferFile_FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_ElectronicNodes_Source_ElectronicNodes_Private_Popup_ENUpdateConfig_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_ElectronicNodes_Source_ElectronicNodes_Private_Popup_ENUpdateConfig_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
