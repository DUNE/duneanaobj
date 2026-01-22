# Changelog
[[Format loosely based on <https://keepachangelog.com/en/0.3.0>]]

##### current

##### [v03_12_00] -- 2025-12-01
* SAND detector specific fields [#53]
* Initialize G4 process codes better [#59]
* Improved beam quality info [#60]
* Storage for reco particle hierarchy relationships [#61]
* Fix automated Doxygen generation [074e1a]

##### [v03_11_00] -- 2025-09-17
* Updated ROOT software stack (v6_26_06b)
* Improved ND track matching [#57, #58]

##### [v03_10_00] -- 2025-06-26
* Storage for muon energy from MCS [#54]

##### [v03_09_00] -- 2025-06-13
* Add fields for storing Pandora PFP (reco particles) [#52]

##### [v03_08_00] -- 2025-05-08
* Add more energy estimator, other info relevant for atmospheric analysis  [#51]

##### [v03_07_00] -- 2025-04-17
* Add convenience navigation functions for ancestry traversal with SRProxy [#50]
* Bump default qual to e26, srproxy to v00.45; eliminate e20

##### [v03_06_01] -- 2024-08-30
* Modernize the cetmodules stuff [#31, #38]
* Track & shower matching bugfix [#41]
* Add new flash match class & fix initialization of run info [#42]
* Touch up `classes_def.xml` [#44]

##### [v03_05_00] -- 2025-05-13
* Add extra reco Enu fields for FD analysis usage [#34]
* Bump ROOT version [#36]
* Touch up `classes_def.xml` [#37]

##### [v03_04_00] -- 2024-03-18
* Bump ROOT, SRProxy versions [#33]

##### [v03_03_00] -- 2024-01-12  (PR #27)
* Store GEANT4 process codes & include documentation links rather than translating them to internal enumeration

##### [v03_02_01] -- 2023-11-14  (PR #26)
* Disable `SRTrueInteraction::genConfigString` for now to work around `free: invalid pointer` issues when deserializing
* Add a few more classes to the dictionary

#####
... more history to be added as time allows ... 
