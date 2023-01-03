#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/Pflanzensensor.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/Pflanzensensor.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=main.c Feuchtigkeit.c buzzer.c display.c picture.c uart.c newSonic.c buttons.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/main.o ${OBJECTDIR}/Feuchtigkeit.o ${OBJECTDIR}/buzzer.o ${OBJECTDIR}/display.o ${OBJECTDIR}/picture.o ${OBJECTDIR}/uart.o ${OBJECTDIR}/newSonic.o ${OBJECTDIR}/buttons.o
POSSIBLE_DEPFILES=${OBJECTDIR}/main.o.d ${OBJECTDIR}/Feuchtigkeit.o.d ${OBJECTDIR}/buzzer.o.d ${OBJECTDIR}/display.o.d ${OBJECTDIR}/picture.o.d ${OBJECTDIR}/uart.o.d ${OBJECTDIR}/newSonic.o.d ${OBJECTDIR}/buttons.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/main.o ${OBJECTDIR}/Feuchtigkeit.o ${OBJECTDIR}/buzzer.o ${OBJECTDIR}/display.o ${OBJECTDIR}/picture.o ${OBJECTDIR}/uart.o ${OBJECTDIR}/newSonic.o ${OBJECTDIR}/buttons.o

# Source Files
SOURCEFILES=main.c Feuchtigkeit.c buzzer.c display.c picture.c uart.c newSonic.c buttons.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/Pflanzensensor.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=ATmega328P
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/87bc4b8af386ef18e94ac1f4b1fb0cb852550e8a .generated_files/flags/default/c1e3170f6c2f4ee99286804d8babe1b1bd4428ea
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/main.o.d" -MT "${OBJECTDIR}/main.o.d" -MT ${OBJECTDIR}/main.o -o ${OBJECTDIR}/main.o main.c 
	
${OBJECTDIR}/Feuchtigkeit.o: Feuchtigkeit.c  .generated_files/flags/default/7adfff49a17d5a3eff4ebce20b9068148fba35e7 .generated_files/flags/default/c1e3170f6c2f4ee99286804d8babe1b1bd4428ea
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Feuchtigkeit.o.d 
	@${RM} ${OBJECTDIR}/Feuchtigkeit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/Feuchtigkeit.o.d" -MT "${OBJECTDIR}/Feuchtigkeit.o.d" -MT ${OBJECTDIR}/Feuchtigkeit.o -o ${OBJECTDIR}/Feuchtigkeit.o Feuchtigkeit.c 
	
${OBJECTDIR}/buzzer.o: buzzer.c  .generated_files/flags/default/1aad556607f804fad9962a020fb4be518867ad7d .generated_files/flags/default/c1e3170f6c2f4ee99286804d8babe1b1bd4428ea
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/buzzer.o.d 
	@${RM} ${OBJECTDIR}/buzzer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/buzzer.o.d" -MT "${OBJECTDIR}/buzzer.o.d" -MT ${OBJECTDIR}/buzzer.o -o ${OBJECTDIR}/buzzer.o buzzer.c 
	
${OBJECTDIR}/display.o: display.c  .generated_files/flags/default/8ca28d486549e0c4d8f398b4cd2d5673fe477462 .generated_files/flags/default/c1e3170f6c2f4ee99286804d8babe1b1bd4428ea
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/display.o.d 
	@${RM} ${OBJECTDIR}/display.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/display.o.d" -MT "${OBJECTDIR}/display.o.d" -MT ${OBJECTDIR}/display.o -o ${OBJECTDIR}/display.o display.c 
	
${OBJECTDIR}/picture.o: picture.c  .generated_files/flags/default/d5924380ba1e96ab0ebd42498a686c51ec278054 .generated_files/flags/default/c1e3170f6c2f4ee99286804d8babe1b1bd4428ea
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/picture.o.d 
	@${RM} ${OBJECTDIR}/picture.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/picture.o.d" -MT "${OBJECTDIR}/picture.o.d" -MT ${OBJECTDIR}/picture.o -o ${OBJECTDIR}/picture.o picture.c 
	
${OBJECTDIR}/uart.o: uart.c  .generated_files/flags/default/38790111f9439d132c187fddfa25431e3a826431 .generated_files/flags/default/c1e3170f6c2f4ee99286804d8babe1b1bd4428ea
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/uart.o.d 
	@${RM} ${OBJECTDIR}/uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/uart.o.d" -MT "${OBJECTDIR}/uart.o.d" -MT ${OBJECTDIR}/uart.o -o ${OBJECTDIR}/uart.o uart.c 
	
${OBJECTDIR}/newSonic.o: newSonic.c  .generated_files/flags/default/7ab451b66efa0d65a0eec540ccc475aab15ab411 .generated_files/flags/default/c1e3170f6c2f4ee99286804d8babe1b1bd4428ea
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/newSonic.o.d 
	@${RM} ${OBJECTDIR}/newSonic.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/newSonic.o.d" -MT "${OBJECTDIR}/newSonic.o.d" -MT ${OBJECTDIR}/newSonic.o -o ${OBJECTDIR}/newSonic.o newSonic.c 
	
${OBJECTDIR}/buttons.o: buttons.c  .generated_files/flags/default/3926405606fe0a69b0aefa4adc56b86691478929 .generated_files/flags/default/c1e3170f6c2f4ee99286804d8babe1b1bd4428ea
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/buttons.o.d 
	@${RM} ${OBJECTDIR}/buttons.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/buttons.o.d" -MT "${OBJECTDIR}/buttons.o.d" -MT ${OBJECTDIR}/buttons.o -o ${OBJECTDIR}/buttons.o buttons.c 
	
else
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/84ae4a1828c8dddc542223e6364c8dd667b6bad8 .generated_files/flags/default/c1e3170f6c2f4ee99286804d8babe1b1bd4428ea
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/main.o.d" -MT "${OBJECTDIR}/main.o.d" -MT ${OBJECTDIR}/main.o -o ${OBJECTDIR}/main.o main.c 
	
${OBJECTDIR}/Feuchtigkeit.o: Feuchtigkeit.c  .generated_files/flags/default/b339db8ef5bea239c5f932097890d510af7368b8 .generated_files/flags/default/c1e3170f6c2f4ee99286804d8babe1b1bd4428ea
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Feuchtigkeit.o.d 
	@${RM} ${OBJECTDIR}/Feuchtigkeit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/Feuchtigkeit.o.d" -MT "${OBJECTDIR}/Feuchtigkeit.o.d" -MT ${OBJECTDIR}/Feuchtigkeit.o -o ${OBJECTDIR}/Feuchtigkeit.o Feuchtigkeit.c 
	
${OBJECTDIR}/buzzer.o: buzzer.c  .generated_files/flags/default/40ee2b9236b49ca312b825f6fcde8488ec6ced2 .generated_files/flags/default/c1e3170f6c2f4ee99286804d8babe1b1bd4428ea
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/buzzer.o.d 
	@${RM} ${OBJECTDIR}/buzzer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/buzzer.o.d" -MT "${OBJECTDIR}/buzzer.o.d" -MT ${OBJECTDIR}/buzzer.o -o ${OBJECTDIR}/buzzer.o buzzer.c 
	
${OBJECTDIR}/display.o: display.c  .generated_files/flags/default/9b9cbf4d85f158469c58b9255d34f52d912e1b0e .generated_files/flags/default/c1e3170f6c2f4ee99286804d8babe1b1bd4428ea
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/display.o.d 
	@${RM} ${OBJECTDIR}/display.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/display.o.d" -MT "${OBJECTDIR}/display.o.d" -MT ${OBJECTDIR}/display.o -o ${OBJECTDIR}/display.o display.c 
	
${OBJECTDIR}/picture.o: picture.c  .generated_files/flags/default/199c742c2bd37d62871a7809609bd324f8b24718 .generated_files/flags/default/c1e3170f6c2f4ee99286804d8babe1b1bd4428ea
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/picture.o.d 
	@${RM} ${OBJECTDIR}/picture.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/picture.o.d" -MT "${OBJECTDIR}/picture.o.d" -MT ${OBJECTDIR}/picture.o -o ${OBJECTDIR}/picture.o picture.c 
	
${OBJECTDIR}/uart.o: uart.c  .generated_files/flags/default/2f1c78f6350675d50901874e7bfbe0da05bc6f9 .generated_files/flags/default/c1e3170f6c2f4ee99286804d8babe1b1bd4428ea
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/uart.o.d 
	@${RM} ${OBJECTDIR}/uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/uart.o.d" -MT "${OBJECTDIR}/uart.o.d" -MT ${OBJECTDIR}/uart.o -o ${OBJECTDIR}/uart.o uart.c 
	
${OBJECTDIR}/newSonic.o: newSonic.c  .generated_files/flags/default/57b3add0a78fd3c4de16e07edac0236b0b197ad0 .generated_files/flags/default/c1e3170f6c2f4ee99286804d8babe1b1bd4428ea
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/newSonic.o.d 
	@${RM} ${OBJECTDIR}/newSonic.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/newSonic.o.d" -MT "${OBJECTDIR}/newSonic.o.d" -MT ${OBJECTDIR}/newSonic.o -o ${OBJECTDIR}/newSonic.o newSonic.c 
	
${OBJECTDIR}/buttons.o: buttons.c  .generated_files/flags/default/e32cccd3640a3c8c1b741bf3e0dc4de9194fbb31 .generated_files/flags/default/c1e3170f6c2f4ee99286804d8babe1b1bd4428ea
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/buttons.o.d 
	@${RM} ${OBJECTDIR}/buttons.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/buttons.o.d" -MT "${OBJECTDIR}/buttons.o.d" -MT ${OBJECTDIR}/buttons.o -o ${OBJECTDIR}/buttons.o buttons.c 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/Pflanzensensor.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/Pflanzensensor.X.${IMAGE_TYPE}.map  -D__DEBUG=1  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"   -gdwarf-2 -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -gdwarf-3     $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/Pflanzensensor.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  -o ${DISTDIR}/Pflanzensensor.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -Wl,--start-group  -Wl,-lm -Wl,--end-group  -Wl,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1
	@${RM} ${DISTDIR}/Pflanzensensor.X.${IMAGE_TYPE}.hex 
	
else
${DISTDIR}/Pflanzensensor.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/Pflanzensensor.X.${IMAGE_TYPE}.map  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -gdwarf-3     $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/Pflanzensensor.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  -o ${DISTDIR}/Pflanzensensor.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -Wl,--start-group  -Wl,-lm -Wl,--end-group 
	${MP_CC_DIR}\\avr-objcopy -O ihex "${DISTDIR}/Pflanzensensor.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "${DISTDIR}/Pflanzensensor.X.${IMAGE_TYPE}.hex"
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
