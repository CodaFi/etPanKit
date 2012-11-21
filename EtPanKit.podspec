Pod::Spec.new do |s|
  s.name     = 'EtPanKit'
  s.version  = '1.0'
  s.license  = 'BSD'
  s.summary  = 'An Objective-C interface for the libEtPan framework for Mac.'
  s.homepage = 'https://github.com/CodaFi/etPanKit'
  s.author   = { 'DINH Viet Hoa' => 'dinh.viet.hoa@gmail.com' }
  s.source   = { :git => 'https://github.com/CodaFi/etPanKit.git'}
  s.description = 'An Objective-C interface for the libEtPan framework for Mac.'
  s.platform = :osx
  s.source_files = 'Source/**/*.{h,m}'
  s.resources = "Resources/**/*.plist"
  s.frameworks = 'Security', 'Foundation'

  s.subspec 'LibEtPan' do |lep|
    lep.name     = 'LibEtPan'
    lep.platform = :osx
    lep.source_files = 'Externals/libetpan/**/*.{h,m,c}'
    lep.libraries = 'libexpat', 'libcrypto', 'libcurl', 'libiconv', 'libsasl', 'libssl'
  end
end