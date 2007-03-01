!defined(ModuleStabilityCheck) {

defineReplace(ModuleStabilityCheck) {
    out=
    for(part, 1) {
        1-=$$part
        contains(QXT_stability,stable):  contains($${part}.stability,+$$PLATFORM):out+=$$part 
        contains(QXT_stability,broken):  contains($${part}.stability,-$$PLATFORM):out+=$$part
        contains(QXT_stability,unknown):!contains($${part}.stability,-$$PLATFORM):!contains($${part}.stability,+$$PLATFORM):out+=$$part
	}
    out += $$QXT_ignore_stability
    return ($$out)
}

defineReplace(ModuleHeaders) {
    out =
    for(part, 1) {
        out += $${part}.h

        for(header, $${part}.headers) {
            out += $$header
		}
	}	 
    return ($$out)
}

defineReplace(ModuleSources) {
    for(part, 1){
        exists($${part}.cpp)out += $${part}.cpp

        for(source, $${part}.sources) {
            out += $$source
        }
    }	 
    return ($$out)
}

defineTest(ModuleBuildDebug) {
    partlist=
    for(part, 1):  partlist+= $$part

    message($$partlist)
    message($$HEADERS)
    message($$SOURCES)
}

