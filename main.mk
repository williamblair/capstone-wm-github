##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=main
ConfigurationName      :=Debug
WorkspacePath          :=/home/bj/Documents/cs498-windowmanager
ProjectPath            :=/home/bj/Documents/cs498-windowmanager
IntermediateDirectory  :=./
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=bj
Date                   :=11/11/17
CodeLitePath           :=/home/bj/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="main.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)X11 $(LibrarySwitch)Xpm 
ArLibs                 :=  "X11" "Xpm" 
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
TERM:=xterm
Objects0=$(IntermediateDirectory)/buttonEvents.c$(ObjectSuffix) $(IntermediateDirectory)/configureEvents.c$(ObjectSuffix) $(IntermediateDirectory)/destroyEvents.c$(ObjectSuffix) $(IntermediateDirectory)/displayEvents.c$(ObjectSuffix) $(IntermediateDirectory)/initCapstone.c$(ObjectSuffix) $(IntermediateDirectory)/keyEvents.c$(ObjectSuffix) $(IntermediateDirectory)/main.c$(ObjectSuffix) $(IntermediateDirectory)/motionEvents.c$(ObjectSuffix) $(IntermediateDirectory)/reparent.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./ || $(MakeDirCommand) ./


$(IntermediateDirectory)/.d:
	@test -d ./ || $(MakeDirCommand) ./

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/buttonEvents.c$(ObjectSuffix): buttonEvents.c $(IntermediateDirectory)/buttonEvents.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/bj/Documents/cs498-windowmanager/buttonEvents.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/buttonEvents.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/buttonEvents.c$(DependSuffix): buttonEvents.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/buttonEvents.c$(ObjectSuffix) -MF$(IntermediateDirectory)/buttonEvents.c$(DependSuffix) -MM buttonEvents.c

$(IntermediateDirectory)/buttonEvents.c$(PreprocessSuffix): buttonEvents.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/buttonEvents.c$(PreprocessSuffix) buttonEvents.c

$(IntermediateDirectory)/configureEvents.c$(ObjectSuffix): configureEvents.c $(IntermediateDirectory)/configureEvents.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/bj/Documents/cs498-windowmanager/configureEvents.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/configureEvents.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/configureEvents.c$(DependSuffix): configureEvents.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/configureEvents.c$(ObjectSuffix) -MF$(IntermediateDirectory)/configureEvents.c$(DependSuffix) -MM configureEvents.c

$(IntermediateDirectory)/configureEvents.c$(PreprocessSuffix): configureEvents.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/configureEvents.c$(PreprocessSuffix) configureEvents.c

$(IntermediateDirectory)/destroyEvents.c$(ObjectSuffix): destroyEvents.c $(IntermediateDirectory)/destroyEvents.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/bj/Documents/cs498-windowmanager/destroyEvents.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/destroyEvents.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/destroyEvents.c$(DependSuffix): destroyEvents.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/destroyEvents.c$(ObjectSuffix) -MF$(IntermediateDirectory)/destroyEvents.c$(DependSuffix) -MM destroyEvents.c

$(IntermediateDirectory)/destroyEvents.c$(PreprocessSuffix): destroyEvents.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/destroyEvents.c$(PreprocessSuffix) destroyEvents.c

$(IntermediateDirectory)/displayEvents.c$(ObjectSuffix): displayEvents.c $(IntermediateDirectory)/displayEvents.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/bj/Documents/cs498-windowmanager/displayEvents.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/displayEvents.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/displayEvents.c$(DependSuffix): displayEvents.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/displayEvents.c$(ObjectSuffix) -MF$(IntermediateDirectory)/displayEvents.c$(DependSuffix) -MM displayEvents.c

$(IntermediateDirectory)/displayEvents.c$(PreprocessSuffix): displayEvents.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/displayEvents.c$(PreprocessSuffix) displayEvents.c

$(IntermediateDirectory)/initCapstone.c$(ObjectSuffix): initCapstone.c $(IntermediateDirectory)/initCapstone.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/bj/Documents/cs498-windowmanager/initCapstone.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/initCapstone.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/initCapstone.c$(DependSuffix): initCapstone.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/initCapstone.c$(ObjectSuffix) -MF$(IntermediateDirectory)/initCapstone.c$(DependSuffix) -MM initCapstone.c

$(IntermediateDirectory)/initCapstone.c$(PreprocessSuffix): initCapstone.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/initCapstone.c$(PreprocessSuffix) initCapstone.c

$(IntermediateDirectory)/keyEvents.c$(ObjectSuffix): keyEvents.c $(IntermediateDirectory)/keyEvents.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/bj/Documents/cs498-windowmanager/keyEvents.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/keyEvents.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/keyEvents.c$(DependSuffix): keyEvents.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/keyEvents.c$(ObjectSuffix) -MF$(IntermediateDirectory)/keyEvents.c$(DependSuffix) -MM keyEvents.c

$(IntermediateDirectory)/keyEvents.c$(PreprocessSuffix): keyEvents.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/keyEvents.c$(PreprocessSuffix) keyEvents.c

$(IntermediateDirectory)/main.c$(ObjectSuffix): main.c $(IntermediateDirectory)/main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/bj/Documents/cs498-windowmanager/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.c$(DependSuffix): main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/main.c$(DependSuffix) -MM main.c

$(IntermediateDirectory)/main.c$(PreprocessSuffix): main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.c$(PreprocessSuffix) main.c

$(IntermediateDirectory)/motionEvents.c$(ObjectSuffix): motionEvents.c $(IntermediateDirectory)/motionEvents.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/bj/Documents/cs498-windowmanager/motionEvents.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/motionEvents.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/motionEvents.c$(DependSuffix): motionEvents.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/motionEvents.c$(ObjectSuffix) -MF$(IntermediateDirectory)/motionEvents.c$(DependSuffix) -MM motionEvents.c

$(IntermediateDirectory)/motionEvents.c$(PreprocessSuffix): motionEvents.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/motionEvents.c$(PreprocessSuffix) motionEvents.c

$(IntermediateDirectory)/reparent.c$(ObjectSuffix): reparent.c $(IntermediateDirectory)/reparent.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/bj/Documents/cs498-windowmanager/reparent.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/reparent.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/reparent.c$(DependSuffix): reparent.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/reparent.c$(ObjectSuffix) -MF$(IntermediateDirectory)/reparent.c$(DependSuffix) -MM reparent.c

$(IntermediateDirectory)/reparent.c$(PreprocessSuffix): reparent.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/reparent.c$(PreprocessSuffix) reparent.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./


