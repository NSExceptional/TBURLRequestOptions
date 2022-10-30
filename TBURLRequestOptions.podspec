
Pod::Spec.new do |s|
  s.name             = 'TBURLRequestOptions'
  s.version          = '1.0.0'
  s.summary          = 'A small, handy library to make HTTP networking easier.'

  s.homepage         = 'https://github.com/NSExceptional/TBURLRequestOptions'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'Tanner Bennett' => 'tannerbennett@me.com' }
  s.source           = { :git => 'https://github.com/NSExceptional/TBURLRequestOptions.git', :tag => s.version.to_s }

  s.requires_arc = true
  s.ios.deployment_target = '7.0'
  s.osx.deployment_target = '10.9'

  s.source_files = 'TBURLRequestOptions/Classes/**/*'
end
